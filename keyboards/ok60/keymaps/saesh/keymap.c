#include QMK_KEYBOARD_H

#define BASE    0
#define FN      1
#define SPECIAL 2

#define _______ KC_TRNS
#define SHFT_LE_BRACKET LSFT(KC_LBRC)
#define SHFT_RI_BRACKET LSFT(KC_RBRC)
#define MEDIA_WIN_NEXT KC_MNXT
#define MEDIA_MAC_NEXT KC_MFFD
#define HOME_ALT MT(MOD_RALT, KC_HOME)
#define LAG_SWAP MAGIC_SWAP_LALT_LGUI
#define LAG_NORM MAGIC_UNSWAP_LALT_LGUI

// Tap Dance Definitions
enum {
  TD_L_BRC_SHFT = 0, // Tap once for bracket, twice for curly braces
  TD_R_BRC_SHFT = 1, // Tap once for bracket, twice for curly braces
  TD_NEXT       = 2, // Media Next macOs, double tap Next windows
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_L_BRC_SHFT] = ACTION_TAP_DANCE_DOUBLE(SHFT_LE_BRACKET, KC_LBRC),
  [TD_R_BRC_SHFT] = ACTION_TAP_DANCE_DOUBLE(SHFT_RI_BRACKET, KC_RBRC),
  [TD_NEXT]       = ACTION_TAP_DANCE_DOUBLE(MEDIA_WIN_NEXT, MEDIA_MAC_NEXT),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* QWERTY - Split Backspace, Split right Shift, Space Cadet Shift
  * ,-----------------------------------------------------------------------------------------.
  * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  \  |  `  |
  * |-----------------------------------------------------------------------------------------+
  * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  {[ |  }] |  Bksp  |
  * |-----------------------------------------------------------------------------------------+
  * | Ctrl    |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
  * |-----------------------------------------------------------------------------------------+
  * | Shift/(   |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  | RShift/)  | FN  |
  * |-----------------------------------------------------------------------------------------+
  * | FN   | LAlt | LGUI |                FN/Space                |Alt/Ho| PgUp | PgDn |  End |
  * `-----------------------------------------------------------------------------------------'
  */
  [BASE] = LAYOUT_60_ansi_split_bksp_rshift(
      KC_GESC,  KC_1,    KC_2,    KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,    KC_9,    KC_0,    KC_MINS,           KC_EQL,            KC_BSLS, KC_GRV,
      KC_TAB,   KC_Q,    KC_W,    KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,    KC_O,    KC_P,    TD(TD_L_BRC_SHFT), TD(TD_R_BRC_SHFT), KC_BSPC,
      KC_LCTL,  KC_A,    KC_S,    KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT,           KC_ENT,
      KC_LSPO,  KC_Z,    KC_X,    KC_C,  KC_V,  KC_B,  KC_N,  KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,           MO(FN),
      MO(FN),   KC_LALT, KC_LGUI,                LT(FN, KC_SPC),                               HOME_ALT,          KC_PGUP,            KC_PGDN, KC_END
  ),

 /* Functions, HHKB arrows, Media keys, Touch Cursor
  * ,-----------------------------------------------------------------------------------------.
  * |     | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 | Ins | Del |
  * |-----------------------------------------------------------------------------------------+
  * |        |     |     |     |     |     | ins | home| up  | end | bcsp| up  |     |   Del  |
  * |-----------------------------------------------------------------------------------------+
  * |         |     |     |     |     |     | pgdn| left| down|right| left|right|   SPECIAL   |
  * |-----------------------------------------------------------------------------------------+
  * | LShift    |     |     |     |     |     | pgup| del |     |     | down| RShift    |     |
  * |-----------------------------------------------------------------------------------------+
  * |      |      |      |                                        | Play | VolDn| VolUp| Next |
  * `-----------------------------------------------------------------------------------------'
  */
  [FN] = LAYOUT_60_ansi_split_bksp_rshift(
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_INS, KC_DEL,
      _______, _______, _______, _______, _______, _______, KC_INS, KC_HOME,   KC_UP,   KC_END, KC_BSPC,   KC_UP, _______,  KC_DEL,
      _______, _______, _______, _______, _______, _______, KC_PGUP, KC_LEFT, KC_DOWN, KC_RIGHT,KC_LEFT, KC_RGHT, MO(SPECIAL),
      KC_LSFT, _______, _______, _______, _______, _______, KC_PGDN,  KC_DEL, _______, _______, KC_DOWN, KC_RSFT, _______,
      _______, _______, _______,                   _______,                            KC_MPLY, KC_VOLD, KC_VOLU, TD(TD_NEXT)
  ),

  /* Special layer to put the keyboard into DFU mode for flashing, swap left alt/gui and sleep mode
  * ,-----------------------------------------------------------------------------------------.
  * | Slep|     |     |     |     |     |     |     |     |     |     |     |     |     |     |
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
      KC_SLEP,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______,  _______,  _______, _______,   RESET, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, LAG_SWAP, LAG_NORM, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______,  _______,  _______,                   _______,                            _______, _______, _______, _______
  ),
};
