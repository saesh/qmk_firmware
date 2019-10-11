#include QMK_KEYBOARD_H
#include "saesh.h"
#include "tapdances.h"
#include "oled.h"
#include "rgb.h"

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
#define KC_OLTOGL   OLTOGL
#define KC_SHCAP    TD(SHFT_CAPS)
#define KC_LOWBCK   LT(_LOWER, KC_BSPC)
#define KC_RAIDEL   LT(_RAISE, KC_DEL)
#define KC_SPALT    LALT_T(KC_SPACE)
#define KC_OS_RSFT  OSM(MOD_RSFT)

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
      XXXXX, XXXXX, XXXXX,  ERMR,  RST, OLTOGL,               SECRET_1, XXXXX,  MRWD,  MFFD, XXXXX,  MAKE,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LTOG,  LHUI,  LSAI,  LVAI,  LSPI, XXXXX,               SECRET_2,  MPLY,  MPRV,  MNXT, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LMOD,  LHUD,  LSAD,  LVAD,  LSPD, XXXXX,                  XXXXX, XXXXX,  VOLD,  VOLU,  MUTE, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  XXXXX, _____, XXXXX,    XXXXX, _____, XXXXX
                              //`--------------------'  `--------------------'
  )
};

void matrix_init_user(void) {}

void matrix_scan_user(void) {}

__attribute__((weak))
layer_state_t layer_state_set_keymap(layer_state_t state) { return state; }

__attribute__((weak))
layer_state_t rgb_layer_state_set(layer_state_t state) { return state; }

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
    state = rgb_layer_state_set(state);

    return layer_state_set_keymap(state);
}

void makeFirmware(void) {
    uint8_t modifier = mod_config(get_mods());
    uint8_t oneshotkey = mod_config(get_oneshot_mods());
    clear_mods();
    clear_oneshot_mods();

    // build the firmware
    send_string_with_delay_P(PSTR("make " QMK_KEYBOARD ":" QMK_KEYMAP), TAP_CODE_DELAY);

    // flash when Shift is pressed
#ifndef MAKE_BOOTLOADER
    if ((modifier | oneshotkey) & MOD_MASK_SHIFT)
#endif
    {
        send_string_with_delay_P(PSTR(":flash"), TAP_CODE_DELAY);
    }


    // flash with RGB matrix modified for right side when Alt is pressed
    if ((modifier | oneshotkey) & MOD_MASK_ALT) {
        send_string_with_delay_P(PSTR(" RGB_MATRIX_SPLIT_RIGHT=yes"), TAP_CODE_DELAY);
    }

    // execute command
    send_string_with_delay_P(PSTR(SS_TAP(X_ENTER)), TAP_CODE_DELAY);
}

__attribute__ ((weak))
bool oled_process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

__attribute__ ((weak))
bool secrets_process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        case KC_MAKE:
            if (!record->event.pressed) {
                makeFirmware();
            }
            break;
    }

    return oled_process_record_user(keycode, record) &&
           secrets_process_record_user(keycode, record);
}

__attribute__ ((weak))
void rgb_on_power_down(void) {}

void suspend_power_down_user(void) {
    rgb_on_power_down();
}

__attribute__ ((weak))
void rgb_on_wakeup(void) {}

void suspend_wakeup_init_user(void) {
    rgb_on_wakeup();
}

__attribute__ ((weak))
void rgb_on_shutdown(void) {}

__attribute__((weak))
void shutdown_keymap(void) {}

void shutdown_user(void) {
    rgb_on_shutdown();
    shutdown_keymap();
}