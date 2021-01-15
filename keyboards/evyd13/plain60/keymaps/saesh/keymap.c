#include QMK_KEYBOARD_H
#include "saesh.h"

#define KC_SEC1 KC_SECRET_1
#define KC_SEC2 KC_SECRET_2
#define KC_SEC3 KC_SECRET_3

enum _layer {
  _BASE,
  _MAC,
  _FN,
  _CTRL,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT_60_tsangan_hhkb(
  KC_ESC,  KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV, \
  KC_TAB,  KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,   \
  KC_LCTL, KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,    \
  KC_LSFT,          KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(_FN),   \
  KC_LCTL, KC_LGUI, KC_LALT,               LT(_FN, KC_SPC),                                   KC_ALGR, KC_RGUI, KC_RCTRL), \

[_MAC] = LAYOUT_60_tsangan_hhkb(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    \
  KC_LGUI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    \
  _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    \
  _______, KC_LALT, KC_LGUI,                            _______,                                     KC_RGUI, KC_ALGR, _______), \


[_FN] = LAYOUT_60_tsangan_hhkb(
  _______, KC_F1,   KC_F2  , KC_F3,   KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_INS , KC_DEL, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_UP  , _______, KC_DEL ,    \
  _______, KC_VOLU, KC_VOLD, KC_MUTE, _______, _______, _______, _______, KC_HOME, KC_PGUP, KC_LEFT, KC_RIGHT,         _______,    \
  _______,          _______, _______, _______, _______, _______, _______, _______, KC_END,  KC_PGDN, KC_DOWN, _______, _______,    \
  _______, _______, _______,                            _______,                                     _______, MO(_CTRL), _______), \

[_CTRL] = LAYOUT_60_tsangan_hhkb(
  _______, KC_SEC1 , KC_SEC2, KC_SEC3, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______ , _______, _______, RESET  , _______, _______, _______, _______, _______, _______, _______, _______, _______,  \
  _______, TG(_MAC), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,  \
  _______,           _______, _______, _______, _______, _______, _______, KC_MAKE, _______, _______, _______, _______, _______,  \
  _______, _______ , _______,                            _______,                                     _______, _______, _______)
};
