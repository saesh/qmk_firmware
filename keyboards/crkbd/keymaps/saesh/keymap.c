#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _LOWER  1
#define _RAISE  2
#define _ADJUST 3
#define _GAME   4

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO

#define KC_LOWER LOWER
#define KC_RAISE RAISE

#define KC_RST   RESET          // Reset controller
#define KC_ERMR  EEP_RST        // EEPROM reset

#define KC_LTOG  RGB_TOG
#define KC_LMOD  RGB_MOD
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LSPI  RGB_SPI
#define KC_LSPD  RGB_SPD

#define KC_CTLTB CTL_T(KC_TAB)  // Ctrl+Tab
#define KC_G(x) G(x)            // GUI
#define KC_GESC GRAVE_ESC       // Grace Esc

#define KC_TG(x) TG(x)

#define KC_OLTOGL OLTOGL

// imports
extern uint8_t is_master;
__attribute__((weak))
void shutdown_keymap(void) {}
void rgb_matrix_update_pwm_buffers(void);
// end imports

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  OLTOGL
};

#ifdef OLED_DRIVER_ENABLE
static bool oled_should_be_off = false;
static uint32_t oled_timer = 0;
const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ';', '\'', ' ', ',', '.', '/', ' ', ' ', ' '};
char keylog_str[6] = {};
char codelog_str[6] = {};

void add_to_keylog(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
        keycode = keycode & 0xFF;
    }

    char name = ' ';
    if (keycode < 60) {
        name = code_to_name[keycode];
    }

    snprintf(keylog_str, sizeof(keylog_str), "%c", name);
    snprintf(codelog_str, sizeof(codelog_str), "%2d", keycode);
}
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc(
  //,-----------------------------------------.                ,-----------------------------------------.
       GESC,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLTB,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN,  QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH,  RSFT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LGUI, LOWER, SPACE,    ENTER, RAISE,  RALT
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc(
  //,-----------------------------------------.                ,-----------------------------------------.
      XXXXX,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0,   DEL,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, XXXXX, XXXXX,  LBRC,  LCBR,  LPRN,                   LEFT,  DOWN,    UP, RIGHT, XXXXX,   INS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, XXXXX, XXXXX,  RBRC,  RCBR,  RPRN,                   HOME,  PGDN,  PGUP,   END,  BSLS,  LALT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,    _____, _____, _____
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_kc(
  //,-----------------------------------------.                ,-----------------------------------------.
      XXXXX,  EXLM,    AT,  HASH,   DLR,  PERC,                   CIRC,  AMPR,  ASTR,  UNDS,  PLUS,  MINS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, XXXXX, XXXXX, XXXXX,   EQL, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,  PIPE,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LALT, XXXXX, XXXXX, XXXXX,   MINS, UNDS,                   TILD,  XXXXX, XXXXX, XXXXX, BSLS, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,    _____, _____, _____
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_kc(
  //,-----------------------------------------.                ,-----------------------------------------.
      XXXXX, XXXXX, XXXXX,  ERMR,  RST, OLTOGL,                  XXXXX, XXXXX,  MRWD,  MFFD, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LTOG,  LHUI,  LSAI,  LVAI,  LSPI, XXXXX,                  XXXXX,  MPLY,  MPRV,  MNXT, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LMOD,  LHUD,  LSAD,  LVAD,  LSPD, XXXXX,                  XXXXX, XXXXX,  VOLD,  VOLU,  MUTE, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  XXXXX, _____, XXXXX,    XXXXX, _____, XXXXX
                              //`--------------------'  `--------------------'
  )
};

void matrix_init_user(void) {}

void matrix_scan_user(void) {}

void persistent_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifdef OLED_DRIVER_ENABLE
        oled_timer = timer_read32();
        add_to_keylog(keycode);
    #endif

    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                persistent_default_layer_set(1UL<<_QWERTY);
            }
            return false;
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
        case OLTOGL:
            if (record->event.pressed) {
                oled_should_be_off = !oled_should_be_off;
            }
    }

    return true;
}

void rgb_matrix_indicators_user(void) {
    switch (biton32(layer_state)) {
        case _LOWER:
            // left side
            if (is_master) rgb_matrix_set_color(16,  0x00, 0xFF, 0x00); // d green
            if (is_master) rgb_matrix_set_color(15,  0x00, 0xFF, 0x00); // c green
            if (is_master) rgb_matrix_set_color(11,  0xFF, 0x00, 0xFF); // f violet
            if (is_master) rgb_matrix_set_color(12,  0xFF, 0x00, 0xFF); // v violet
            if (is_master) rgb_matrix_set_color( 8,  0xFF, 0x80, 0x00); // g orange
            if (is_master) rgb_matrix_set_color( 7,  0xFF, 0x80, 0x00); // b orange
            // right side
            if (!is_master) rgb_matrix_set_color(8,  0xFF, 0x00, 0x00); // h red
            if (!is_master) rgb_matrix_set_color(11, 0xFF, 0x00, 0x00); // j red
            if (!is_master) rgb_matrix_set_color(16, 0xFF, 0x00, 0x00); // k red
            if (!is_master) rgb_matrix_set_color(19, 0xFF, 0x00, 0x00); // l red
            break;
        case _RAISE:
            if (is_master) rgb_matrix_set_color(12, 0xFF, 0xFF, 0x00); // v yellow
            if (is_master) rgb_matrix_set_color( 7, 0xFF, 0x00, 0x00); // b red
            break;
    }
}

void suspend_power_down_user(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_suspend_state(true);
#endif
}

void suspend_wakeup_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_suspend_state(false);
#endif
}

static void set_background_red(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_color_all( 0xFF, 0x00, 0x00 );
    rgb_matrix_update_pwm_buffers();
#endif
}

/* on user initiated reset */
void shutdown_user(void) {
    set_background_red();
    shutdown_keymap();
}

#ifdef OLED_DRIVER_ENABLE

// rotate both OLEDs by 270, orientiation is vertical
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_master) {
        return OLED_ROTATION_270;
    }
    
    return rotation;
}

static bool layer_is(uint8_t layer) {
    return get_highest_layer(layer_state) == layer;
}

static void render_layers(void) {
    oled_write_P(PSTR(" BASE"), layer_is(_QWERTY));
    oled_write_P(PSTR("LOWER"), layer_is(_LOWER));
    oled_write_P(PSTR("RAISE"), layer_is(_RAISE));
    oled_write_P(PSTR("ADJUS"), layer_is(_ADJUST));
}

static void render_keylog(void) {
    oled_write_ln(keylog_str, false);
}

static void render_codelog(void) {
    oled_write_ln(codelog_str, false);
}

static void render_empty_line(void) {
    oled_write_P(PSTR("\n"), false);
}

static void render_qmk_info(void) {
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
    } else {
        render_qmk_info();
    }
}

#endif // OLED_DRIVER_ENABLE
