#include QMK_KEYBOARD_H
#include "saesh.h"

#define BASE    0
#define FN      1
#define SPECIAL 2

#define LAG_SWAP MAGIC_SWAP_LALT_LGUI
#define LAG_NORM MAGIC_UNSWAP_LALT_LGUI

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* QWERTY - Split Backspace, Split right Shift, Space Cadet Shift
  * ,-----------------------------------------------------------------------------------------.
  * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  \  | Del |
  * |-----------------------------------------------------------------------------------------+
  * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  {[ |  }] |   BS   |
  * |-----------------------------------------------------------------------------------------+
  * | Ctrl    |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
  * |-----------------------------------------------------------------------------------------+
  * | Shift/(   |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  | RShift/)  | FN  |
  * |-----------------------------------------------------------------------------------------+
  * | CAPS | LGUI | LAlt |                 Space                  | RAlt | RGUI |      |      |
  * `-----------------------------------------------------------------------------------------'
  */
  [BASE] = LAYOUT_60_ansi_split_bksp_rshift(
      CK_EGT,   KC_1,    KC_2,    KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,    KC_9,    KC_0,    KC_MINS,           KC_EQL,            KC_BSLS, KC_DEL,
      KC_TAB,   KC_Q,    KC_W,    KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,    KC_O,    KC_P,    KC_LBRC , KC_RBRC, KC_BSPC,
      KC_LCTL,  KC_A,    KC_S,    KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT,           KC_ENTER,
      KC_LSFT,  KC_Z,    KC_X,    KC_C,  KC_V,  KC_B,  KC_N,  KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,           MO(FN),
      XXXXXXX,  KC_LGUI, KC_LALT,                        KC_SPC,                                KC_RALT,           KC_RGUI,         XXXXXXX, XXXXXXX
  ),

 /* Functions, HHKB arrows, Media keys, Touch Cursor
  * ,-----------------------------------------------------------------------------------------.
  * | Pwr | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 | Ins | Del |
  * |-----------------------------------------------------------------------------------------+
  * | Caps   |     | Play|     |     |     |     |     |     |     |     |  up |     |        |
  * |-----------------------------------------------------------------------------------------+
  * |         | VolD| VolU| Mute|     |     |     |     | Home| PgUp| left|right|             |
  * |-----------------------------------------------------------------------------------------+
  * | LShift    |     |     |     |     |     |     |     | End | PgDn| down| RShift    |     |
  * |-----------------------------------------------------------------------------------------+
  * |      |      |      |                                        | Spec |      |      |      |
  * `-----------------------------------------------------------------------------------------'
  */
  [FN] = LAYOUT_60_ansi_split_bksp_rshift(
      _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,   KC_F12,  KC_INS, KC_DEL,
      _______, _______, KC_MPLY, _______, _______, _______, _______, _______, _______, _______, _______,  KC_UP,    _______,  _______,
      KC_CAPS, KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, _______, _______, KC_HOME, KC_PGUP, KC_LEFT,  KC_RIGHT, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, KC_END,  KC_PGDN, KC_DOWN,  _______,  _______,
      _______, _______, _______,                   _______,                            MO(SPECIAL), _______, _______, _______
  ),

  /* Special layer to put the keyboard into DFU mode for flashing, swap left alt/gui and sleep mode
  * ,-----------------------------------------------------------------------------------------.
  * | Slep|     |     |     |     |     |     |     |     |     |     |     |     |     | Make|
  * |-----------------------------------------------------------------------------------------+
  * |        |     |     |     |RESET|     |     |     |     |     |     |     |     |        |
  * |-----------------------------------------------------------------------------------------+
  * |         |AG SW|AG NO|     |     |     |     |     |     |     |     |     |             |
  * |-----------------------------------------------------------------------------------------+
  * |           |     |     |     |     |     |     |     |     |     |     |           |     |
  * |-----------------------------------------------------------------------------------------+
  * |      |      |      |                                        |      |      |      |      |
  * `-----------------------------------------------------------------------------------------'
  */
  [SPECIAL] = LAYOUT_60_ansi_split_bksp_rshift(
      KC_SLEP,  KC_SECRET_1,  KC_SECRET_2, KC_SECRET_3, KC_SECRET_4, KC_SECRET_5, _______, _______, _______, _______, _______, _______, _______, _______, KC_MAKE,
      _______,  _______,  _______, _______,   RESET, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, LAG_SWAP, LAG_NORM, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______,  _______,  _______,                   _______,                            _______, _______, _______, _______
  ),
};
