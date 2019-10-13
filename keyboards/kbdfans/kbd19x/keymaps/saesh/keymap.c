#include QMK_KEYBOARD_H
#include "keymap_extras/keymap_german.h"

#define _QWERTZ 0

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTZ] = LAYOUT_iso(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  RGB_MOD,               KC_PSCR, KC_SLCK, KC_PAUS, KC_PGDN, \
        DE_CIRC, DE_1,    DE_2,    DE_3,    DE_4,    DE_5,    DE_6,    DE_7,    DE_8,    DE_9,    DE_0,    DE_SS,   DE_ACUT, KC_BSPC,               KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, \
        KC_TAB,  DE_Q,    DE_W,    DE_E,    DE_R,    DE_T,    DE_Z,    DE_U,    DE_I,    DE_O,    DE_P,    DE_UE,   DE_PLUS, KC_ENT,                KC_P7,   KC_P8,   KC_P9,   KC_PPLS, \
        KC_CAPS, DE_A,    DE_S,    DE_D,    DE_F,    DE_G,    DE_H,    DE_J,    DE_K,    DE_L,    DE_OE,   DE_AE,   DE_HASH,                        KC_P4,   KC_P5,   KC_P6,            \
        KC_LSFT, DE_LESS, DE_Y,    DE_X,    DE_C,    DE_V,    DE_B,    DE_N,    DE_M,    DE_COMM, DE_DOT,  DE_MINS,     KC_RSFT,   KC_UP,           KC_P1,   KC_P2,   KC_P3,   KC_PENT, \
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                    KC_RALT, KC_RGUI, KC_RCTL,       KC_LEFT, KC_DOWN, KC_RGHT,         KC_P0,   KC_PDOT           \
    )
};