#include QMK_KEYBOARD_H // sprintf
#include "saesh.h" // layer codes
#include "oled.h"
#include "version.h"
extern uint8_t is_master;

bool oled_should_be_off = false;
uint32_t time_since_boot = 0;
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
    time_since_boot = timer_read32();

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
    oled_write_ln_P(PSTR(QMK_BUILDDATE), false);
    oled_write_ln_P(PSTR(GIT_HASH), false);
    oled_write_ln_P(PSTR(KEYMAP_BRANCH), false);
}

void render_corne_logo(void) {
    static const char PROGMEM corne_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

    render_empty_line();
    oled_write_P(corne_logo, false);
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
        if (timer_elapsed32(time_since_boot) < 5000) {
            render_qmk_info();
            return;
        }

        render_corne_logo();
        oled_scroll_left();
    }
}