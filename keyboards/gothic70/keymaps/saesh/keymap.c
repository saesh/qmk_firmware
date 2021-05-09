#include QMK_KEYBOARD_H
#include "saesh.h"

#define KC_SEC1 KC_SECRET_1
#define KC_SEC2 KC_SECRET_2
#define KC_SEC3 KC_SECRET_3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
     KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL, KC_BSLS,  KC_GRV,          KC_HOME, \
     KC_TAB,    KC_QUIT, KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC, KC_BSPC,           KC_INS, \
    KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,           KC_ENT,           KC_END, \
    KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   MO(2),    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,          KC_RSFT,            KC_UP,          \
    KC_LCTL, KC_LGUI, KC_LALT,           KC_SPC,   MO(1),          KC_BSPC,          KC_RALT,                   KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT  \
  ),

  [1] = LAYOUT(
    _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_INS,  KC_DEL,          _______, \
    _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,  KC_DEL,          _______, \
    _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,          RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______,          _______,          _______, \
    _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______, RGB_TOG, RGB_HUD, RGB_SAD, RGB_VAD, _______,          _______,          _______,          \
    _______, _______, _______,          _______, _______,           KC_DEL,          _______,                   _______,          _______, _______, _______  \
  ),

  [2] = LAYOUT(
    KC_SLEP, KC_SEC1, KC_SEC2, KC_SEC3, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, \
    _______, _______, _______, _______,   RESET, _______,          _______, _______, _______, _______, _______, _______, _______, _______,          _______, \
    _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,          _______,          _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MAKE, _______, _______, _______,          _______,          _______,          \
    _______, _______, _______,          _______, _______,          _______,          _______,                   _______,          _______, _______, _______  \
  )
};

void matrix_init_keymap(void) {
  // set CapsLock LED to output and low
  setPinOutput(F7);
  writePinLow(F7);
  // set NumLock LED to output and low
  setPinOutput(F6);
  writePinLow(F6);
  // set ScrollLock LED to output and low
  setPinOutput(F5);
  writePinLow(F5);
}

uint32_t layer_state_set_keymap(uint32_t state) {
  if (state & (1<<1)) {
    writePinHigh(F5);
  } else if (state & (1<<2)) {
    writePinLow(F5);
    writePinHigh(F6);
  } else if (state & (1<<3)) {
    writePinHigh(F5);
    writePinHigh(F6);
  } else {
    writePinLow(F5);
    writePinLow(F6);
  }
  return state;
}

void led_set_keymap(uint8_t usb_led) {
  if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
    writePinHigh(F7);
  } else {
    writePinLow(F7);
  }
}
