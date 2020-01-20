#include QMK_KEYBOARD_H

#include "quantum.h"
#include "version.h"

enum my_layers {
  _NUMPAD = 0,
  _NAVKEY,
  _MEDIA,
  _RGB,
  _FN1PAD,
};

enum custom_keys {
  U_LAYR = SAFE_RANGE,
  D_LAYR,
  KC_MAKE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_NUMPAD] = LAYOUT(
	KC_7,   KC_8, KC_9,
	KC_4,   KC_5, KC_6,
	KC_1,   KC_2, KC_3,
	U_LAYR, KC_0, KC_NO),

  [_NAVKEY] = LAYOUT(
	KC_HOME, KC_INS,  KC_PGUP,
	KC_END,  KC_UP,   KC_PGDN,
	KC_LEFT, KC_DOWN, KC_RGHT,
	U_LAYR,  KC_NO,   D_LAYR),

  [_MEDIA] = LAYOUT(
	KC_MUTE, KC_VOLD, KC_VOLU,
	KC_NO,   KC_MPLY, KC_NO,
	KC_NO,   KC_NO,   KC_NO,
	U_LAYR,  KC_NO,   D_LAYR),

  [_RGB] = LAYOUT(
	RGB_SAI, RGB_VAI, RGB_HUI,
	RGB_SAD, RGB_VAD, RGB_HUD,
	RGB_TOG, RGB_MOD, KC_NO,
	U_LAYR,  KC_NO,   D_LAYR),

  [_FN1PAD] = LAYOUT(
	KC_NO,   KC_NO,   KC_NO,
	KC_NO,   KC_NO,   RESET,
	KC_NO,   KC_NO,   KC_MAKE,
	KC_LCTL, KC_LSFT, D_LAYR)
};

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  keypos_t key;
  uint8_t current_layer;
  uint8_t next_layer;
  switch (keycode) {
  case U_LAYR: //cycles up the layers
    if (!record->event.pressed) {
      current_layer = layer_switch_get_layer(key);
      next_layer = current_layer+1;
      layer_move(next_layer);
    }
    break;
  case D_LAYR: //cycles down the layers
    if (!record->event.pressed) {
      current_layer = layer_switch_get_layer(key);
      next_layer = current_layer-1;
      layer_move(next_layer);
    }
    break;
  case KC_MAKE:
    if (!record->event.pressed) {
      uint8_t mods = get_mods();
      clear_mods();

      if (mods & MOD_MASK_CTRL) {
        send_string_with_delay_P(PSTR("sudo ./util/docker_build.sh " QMK_KEYBOARD ":" QMK_KEYMAP), TAP_CODE_DELAY);
      } else {
        send_string_with_delay_P(PSTR("make " QMK_KEYBOARD ":" QMK_KEYMAP), TAP_CODE_DELAY);
      }

      if (mods & MOD_MASK_SHIFT) {
        send_string_with_delay_P(PSTR(":flash"), TAP_CODE_DELAY);
      }

      send_string_with_delay_P(PSTR(SS_TAP(X_ENTER)), 10);

      if (mods & MOD_MASK_SHIFT) {
        reset_keyboard();
      }
    }
    break;
  }
  return true;
};

void matrix_init_user(void) {
  rgblight_setrgb(0xff, 0x80, 0x00);
};

uint32_t layer_state_set_user(uint32_t state) {
  switch (biton32(state)) {
    case 0: // NUM
      rgblight_setrgb(RGB_ORANGE);
      break;
    case 1: // NAV
      rgblight_setrgb(RGB_MAGENTA);
      break;
    case 2: // MEDIA
      rgblight_setrgb(RGB_TEAL);
      break;
    case 3: // RGB
      rgblight_setrgb(RGB_WHITE);
      break;
    case 4: // FN
      rgblight_setrgb(RGB_RED);
      break;
    default: //  for any other layers, or the default layer
      rgblight_setrgb(RGB_ORANGE);
      break;
    }
  return state;
}
