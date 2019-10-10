#include QMK_KEYBOARD_H
#include "saesh.h"
#include "tapdances.h"
#include "oled.h"

#define KC______    KC_TRNS
#define KC_XXXXX    KC_NO

#define KC_LOWER    LOWER
#define KC_RAISE    RAISE

#define KC_RST      RESET          // Reset controller
#define KC_ERMR     EEP_RST        // EEPROM reset

#define KC_LTOG     RGB_TOG
#define KC_LMOD     RGB_MOD
#define KC_LHUI     RGB_HUI
#define KC_LHUD     RGB_HUD
#define KC_LSAI     RGB_SAI
#define KC_LSAD     RGB_SAD
#define KC_LVAI     RGB_VAI
#define KC_LVAD     RGB_VAD
#define KC_LSPI     RGB_SPI
#define KC_LSPD     RGB_SPD

#define KC_CTLTB    CTL_T(KC_TAB)  // Ctrl+Tab
#define KC_GESC     GRAVE_ESC      // Grace Esc
#define KC_OLTOGL   OLTOGL
#define KC_SHCAP    TD(SHFT_CAPS)
#define KC_LOWBCK   LT(_LOWER, KC_BSPC)
#define KC_RAIDEL   LT(_RAISE, KC_DEL)
#define KC_SPALT    LALT_T(KC_SPACE)
#define KC_OS_RSFT  OSM(MOD_RSFT)

extern uint8_t is_master;

__attribute__ ((weak))
bool oled_process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc(
  //,-----------------------------------------.                ,-----------------------------------------.
       GESC,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLTB,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN,  QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      SHCAP,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH, OS_RSFT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LGUI, SPALT,LOWBCK,   RAIDEL, ENTER,  RALT
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc(
  //,-----------------------------------------.                ,-----------------------------------------.
      XXXXX, XXXXX, XXXXX,  LBRC,  LCBR,  LPRN,                   RPRN,  RCBR,  RBRC, XXXXX, XXXXX,   DEL,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, XXXXX, XXXXX, XXXXX,   EQL,  MINS,                   LEFT,  DOWN,    UP, RIGHT, XXXXX,   INS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, XXXXX, XXXXX,  HASH,  PLUS,  UNDS,                   HOME,  PGDN,  PGUP,   END,  BSLS,  LALT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,    _____, _____, _____
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_kc(
  //,-----------------------------------------.                ,-----------------------------------------.
       TILD,  EXLM,    AT,  HASH,   DLR,  PERC,                   CIRC,  AMPR,  ASTR,  UNDS,  PLUS,  MINS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0,   F11,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LALT,    F1,    F2,    F3,    F4,    F5,                     F6,    F7,    F8,    F9,   F10,   F12,\
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

__attribute__((weak))
layer_state_t layer_state_set_keymap(layer_state_t state) { return state; }

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
// #ifdef RGB_MATRIX_ENABLE
//     state = layer_state_set_rgb(state);
// #endif
    return layer_state_set_keymap(state);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return oled_process_record_user(keycode, record);
}

void rgb_matrix_indicators_user(void) {
    switch (biton32(layer_state)) {
        case _LOWER:
            // left side
            if (is_master) rgb_matrix_set_color(17,  0x00, 0xFF, 0x00); // e green
            if (is_master) rgb_matrix_set_color(10,  0xFF, 0x00, 0xFF); // r violet
            if (is_master) rgb_matrix_set_color( 9,  0xFF, 0x80, 0x00); // t orange
            
            // right side
            if (!is_master) rgb_matrix_set_color(17,  0x00, 0xFF, 0x00); // i green
            if (!is_master) rgb_matrix_set_color(10,  0xFF, 0x00, 0xFF); // u violet
            if (!is_master) rgb_matrix_set_color( 9,  0xFF, 0x80, 0x00); // y orange

            if (!is_master) rgb_matrix_set_color(8,  0xFF, 0xFF, 0x00); // h yellow
            if (!is_master) rgb_matrix_set_color(11, 0xFF, 0x00, 0x00); // j red
            if (!is_master) rgb_matrix_set_color(16, 0x00, 0xFF, 0x00); // k green
            if (!is_master) rgb_matrix_set_color(19, 0x00, 0x00, 0xFF); // l blue

            if (!is_master) rgb_matrix_set_color(24, 0xFF, 0x00, 0x00); // del red
            if (!is_master) rgb_matrix_set_color(25, 0x00, 0xFF, 0x00); // ' green
            break;
        case _RAISE:
            if (is_master) rgb_matrix_set_color(22, 0xFF, 0x00, 0x51); // a white
            if (is_master) rgb_matrix_set_color(19, 0xFF, 0xFF, 0xFF); // s white
            if (is_master) rgb_matrix_set_color(16, 0xFF, 0x00, 0x51); // d white
            if (is_master) rgb_matrix_set_color(11, 0xFF, 0xFF, 0xFF); // f white
            if (is_master) rgb_matrix_set_color( 8, 0xFF, 0x00, 0x51); // g white

            if (!is_master) rgb_matrix_set_color( 8, 0xFF, 0xFF, 0xFF); // h white
            if (!is_master) rgb_matrix_set_color(11, 0xFF, 0x00, 0x51); // j white
            if (!is_master) rgb_matrix_set_color(16, 0xFF, 0xFF, 0xFF); // k white
            if (!is_master) rgb_matrix_set_color(19, 0xFF, 0x00, 0x51); // l white
            if (!is_master) rgb_matrix_set_color(22, 0xFF, 0xFF, 0xFF); // ; white
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

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_update_pwm_buffers(void);
#endif

void set_background_red(void) {
    rgb_matrix_set_color_all( 0xFF, 0x00, 0x00 );
    rgb_matrix_update_pwm_buffers();
}

/* on user initiated reset */
__attribute__((weak))
void shutdown_keymap(void) {}

void shutdown_user(void) {
#ifdef RGB_MATRIX_ENABLE
    set_background_red();
#endif
    shutdown_keymap();

}
