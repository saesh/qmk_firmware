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
#define KC_QUIT SGUI(KC_Q)      // i3 exit program
#define KC_GESC GRAVE_ESC       // Grace Esc

#define KC_M1 SGUI(KC_1)        // Move to first workspace
#define KC_M2 SGUI(KC_2)
#define KC_M3 SGUI(KC_3)
#define KC_M4 SGUI(KC_4)
#define KC_WSL G(C(KC_LEFT))    // Cycle to workspace left
#define KC_WSR G(C(KC_RIGHT))   // Cycle to workspace right

#define KC_TG(x) TG(x)

extern uint8_t is_master;

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  GAME
};

#ifdef OLED_DRIVER_ENABLE
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
      CTLTB, XXXXX, XXXXX,  LBRC,  LCBR,  LPRN,                   LEFT,  DOWN,    UP, RIGHT,   WSL,   WSR,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LALT, XXXXX, XXXXX,  RBRC,  RCBR,  RPRN,                   HOME,  PGDN,  PGUP,   END,  BSLS,   INS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LGUI, LOWER, SPACE,    ENTER, RAISE,  QUIT
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_kc(
  //,-----------------------------------------.                ,-----------------------------------------.
      XXXXX,  EXLM,    AT,  HASH,   DLR,  PERC,                   CIRC,  AMPR,  ASTR,  UNDS,  PLUS,  MINS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLTB, XXXXX, XXXXX, XXXXX,   EQL, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,  PIPE,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LALT, XXXXX, XXXXX, XXXXX,   MINS, UNDS,                   TILD,  XXXXX, XXXXX, XXXXX, BSLS,  RSFT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LGUI, LOWER, SPACE,    ENTER, RAISE, XXXXX
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_kc(
  //,-----------------------------------------.                ,-----------------------------------------.
  TG(_GAME), XXXXX, XXXXX,  ERMR,  RST,  XXXXX,                  XXXXX, XXXXX,  MRWD,  MFFD, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LTOG,  LHUI,  LSAI,  LVAI,  LSPI, XXXXX,                  XXXXX,  MPLY,  MPRV,  MNXT, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LMOD,  LHUD,  LSAD,  LVAD,  LSPD, XXXXX,                  XXXXX, XXXXX,  VOLD,  VOLU,  MUTE, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  XXXXX, LOWER, XXXXX,    XXXXX, RAISE, XXXXX
                              //`--------------------'  `--------------------'
  ),

  // Apex Legends
  [_GAME] = LAYOUT_kc(
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,     Q,     W,     E,     R,     T,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     A,     S,     D,     F,     G,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LCTL,     Z,     X,     C,     V,     B,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                      M,     J , SPACE,   TG(_GAME), XXXXX, XXXXX
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
    }

    return true;
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

#ifdef OLED_DRIVER_ENABLE

// rotate both OLEDs by 270, orientiation is vertical
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

static bool layer_is(uint8_t layer) {
    return get_highest_layer(layer_state) == layer;
}

static void render_layers(void) {
    oled_write_P(PSTR(" BASE"), layer_is(_QWERTY));
    oled_write_P(PSTR("LOWER"), layer_is(_LOWER));
    oled_write_P(PSTR("RAISE"), layer_is(_RAISE));
    oled_write_P(PSTR("ADJUS"), layer_is(_ADJUST));
    oled_write_P(PSTR(" GAME"), layer_is(_GAME));
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

void oled_task_user(void) {
    // disable OLED on idle and do not proceed
    if (timer_elapsed32(oled_timer) > 20000) {
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
    }
}

#endif // OLED_DRIVER_ENABLE
