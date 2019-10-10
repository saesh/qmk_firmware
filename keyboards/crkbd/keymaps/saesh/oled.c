#include QMK_KEYBOARD_H // sprintf
#include "saesh.h" // layer codes
#include "oled.h"
extern uint8_t is_master;

bool oled_should_be_off = false;
uint32_t oled_timer = 0;
const char PROGMEM code_to_name[0xFF] = {
//   0    1    2    3    4    5    6    7    8    9    A    B    c    D    E    F
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',  // 0x
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2',  // 1x
    '3', '4', '5', '6', '7', '8', '9', '0',  20,  19,  17,  26,  22, '-', '=', '[',  // 2x
    ']','\\', '#', ';','\'', '`', ',', '.', '/', 128, ' ', ' ', ' ', ' ', ' ', ' ',  // 3x
    ' ', ' ', ' ', ' ', ' ', ' ', 'P', 'S', ' ', ' ', ' ', ' ',  16, ' ', ' ',  26,  // 4x
     27,  25,  24, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 5x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 6x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 7x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 8x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 9x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ax
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Bx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Cx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Dx
    'C', 'S', 'A', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ex
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '        // Fx
};

char codelog_str[6] = {' ', 'c', 'o', 'd', 'e'};
char keylog_str[6]  = {' ', 'k', 'e', 'y', ' '};

void add_to_keylog(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) || (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) {
        keycode = keycode & 0xFF;
    } else if (keycode > 0xFF) {
        keycode = 0;
    }

    char name = ' ';
    if (keycode < (sizeof(code_to_name) / sizeof(char))) {
        name = pgm_read_byte(&code_to_name[keycode]);
    }

    snprintf(codelog_str, sizeof(codelog_str), "%5d", keycode);
    snprintf(keylog_str, sizeof(keylog_str), "    %c", name);
}

bool oled_process_record_user(uint16_t keycode, keyrecord_t *record) {
    oled_timer = timer_read32();
    add_to_keylog(keycode);

    switch (keycode) {
        case OLTOGL:
            if (record->event.pressed) {
                oled_should_be_off = !oled_should_be_off;
            }
    }

    return true;
}

// rotate both OLEDs by 270, orientiation is vertical
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_master) {
        return OLED_ROTATION_270;
    }
    
    return rotation;
}

bool layer_is(uint8_t layer) {
    return get_highest_layer(layer_state) == layer;
}

void render_layers(void) {
    oled_write_P(PSTR(" BASE"), layer_is(_QWERTY));
    oled_write_P(PSTR("LOWER"), layer_is(_LOWER));
    oled_write_P(PSTR("RAISE"), layer_is(_RAISE));
    oled_write_P(PSTR("ADJUS"), layer_is(_ADJUST));
}

void render_codelog(void) {
    oled_write(codelog_str, false);
}

void render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_empty_line(void) {
    oled_write_P(PSTR("\n"), false);
}

void render_mod_status(void) {
    uint8_t modifiers = get_mods()|get_oneshot_mods();
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
}

void render_keylock_status(void) {
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(PSTR("  "), false);
    oled_write_P(PSTR("N"), led_usb_state & (1 << USB_LED_NUM_LOCK));
    oled_write_P(PSTR("C"), led_usb_state & (1 << USB_LED_CAPS_LOCK));
    oled_write_P(PSTR("S"), led_usb_state & (1 << USB_LED_SCROLL_LOCK));
}

void render_qmk_info(void) {
    oled_write_ln_P(PSTR("QMK " QMK_VERSION_TAG), false);
    oled_write_ln_P(PSTR(BUILD_TIMESTAMP), false);
    oled_write_ln_P(PSTR(GIT_HASH), false);
    oled_write_ln_P(PSTR(KEYMAP_BRANCH), false);
}

void oled_task_user(void) {
    // disable OLED on idle and do not proceed
    if (oled_should_be_off == true || timer_elapsed32(oled_timer) > 20000) {
        oled_off();
        return;
    } else {
        oled_on();
    }

    if (is_master) {
        render_layers();
        render_empty_line();
        render_codelog();
        render_keylog();
        render_empty_line();
        render_mod_status();
        render_keylock_status();
    } else {
        render_qmk_info();
    }
}