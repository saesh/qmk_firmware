#include QMK_KEYBOARD_H

#include "quantum.h"
#include "version.h"

enum my_layers {
  _NUMPAD = 0,
  _NAVKEY,
  _KERBAL,
  _MEDIA,
  _RGB,
  _FN1PAD,
};

enum custom_keys {
  U_LAYR = SAFE_RANGE,
  D_LAYR,
  KC_MAKE,
  KC_SAFE
};

#define DEFAULT_RBG_MODE 1
static uint8_t current_rgb_mode = 1;
static uint16_t current_rgb_hue = 30;
static uint16_t current_rgb_sat = 255;
static uint16_t current_rgb_val = 200;

void save_rgb(void) {
  current_rgb_mode = rgblight_get_mode();
  current_rgb_hue = rgblight_get_hue();
  current_rgb_val = rgblight_get_val();
  current_rgb_sat = rgblight_get_sat();
}

void restore_rgb(void) {
  rgblight_mode(current_rgb_mode);
  rgblight_sethsv(current_rgb_hue, current_rgb_sat, current_rgb_val);
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_NUMPAD] = LAYOUT(
	KC_7,   KC_8, KC_9,
	KC_4,   KC_5, KC_6,
	KC_1,   KC_2, KC_3,
	U_LAYR, KC_0, KC_NO),

  [_NAVKEY] = LAYOUT(
	KC_HOME, KC_UP,   KC_PGUP,
	KC_LEFT, KC_ENT,  KC_RGHT,
	KC_END,  KC_DOWN, KC_PGDN,
	U_LAYR,  KC_INS,  D_LAYR),

  [_KERBAL] = LAYOUT(
    KC_DOT,  KC_F5,    KC_T,
	KC_COMM, KC_M,     KC_R,
	KC_G,    KC_SPACE, KC_NO,
	U_LAYR,  KC_LALT,  D_LAYR),

  [_MEDIA] = LAYOUT(
	KC_MUTE, KC_VOLD, KC_VOLU,
	KC_MPRV, KC_MPLY, KC_MNXT,
	KC_NO,   KC_NO,   KC_NO,
	U_LAYR,  KC_NO,   D_LAYR),

  [_RGB] = LAYOUT(
	RGB_SAI, RGB_VAI, RGB_HUI,
	RGB_SAD, RGB_VAD, RGB_HUD,
	RGB_TOG, RGB_MOD, KC_NO,
	U_LAYR,  KC_SAFE, D_LAYR),

  [_FN1PAD] = LAYOUT(
	KC_PWR,  KC_NO,   KC_NO,
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
  case KC_SAFE:
    if (!record->event.pressed) {
      save_rgb();
    }
    break;
  }
  return true;
};

void matrix_init_kb(void) {
   DDRD &= ~(1<<5);
   PORTD &= ~(1<<5);

   DDRB &= ~(1<<0);
   PORTB &= ~(1<<0);
}

void matrix_init_user(void) {
};

bool rgb_colors_read = false;

void keyboard_post_init_user(void) {
  if (!rgb_colors_read) {
    save_rgb();
    rgb_colors_read = true;
  }
}

uint16_t layer_indicator_timer;
bool indicator_triggered = false;

uint32_t layer_state_set_user(uint32_t state) {
  switch (biton32(state)) {
    case _NUMPAD:
      rgblight_sethsv_noeeprom(current_rgb_hue, current_rgb_sat, current_rgb_val);
      rgblight_mode_noeeprom(current_rgb_mode);
      indicator_triggered = false;
      break;
    case _NAVKEY:
      rgblight_sethsv_noeeprom(HSV_MAGENTA);
      rgblight_mode_noeeprom(1);
      layer_indicator_timer = timer_read();
      indicator_triggered = true;
      break;
    case _KERBAL:
      rgblight_sethsv_noeeprom(HSV_GREEN);
      rgblight_mode_noeeprom(1);
      layer_indicator_timer = timer_read();
      indicator_triggered = true;
      break;
    case _MEDIA:
      rgblight_sethsv_noeeprom(HSV_TEAL);
      rgblight_mode_noeeprom(1);
      layer_indicator_timer = timer_read();
      indicator_triggered = true;
      break;
    case _RGB:
      rgblight_sethsv_noeeprom(HSV_WHITE);
      rgblight_mode_noeeprom(1);
      layer_indicator_timer = timer_read();
      indicator_triggered = true;
      break;
    case _FN1PAD:
      rgblight_sethsv_noeeprom(HSV_RED);
      rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);
      indicator_triggered = false;
      break;
    default:
      rgblight_sethsv_noeeprom(current_rgb_hue, current_rgb_sat, current_rgb_val);
      rgblight_mode_noeeprom(current_rgb_mode);
      indicator_triggered = false;
      break;
    }
  return state;
}

void matrix_scan_user(void) {
  if (indicator_triggered && (timer_elapsed(layer_indicator_timer) > 750)) {
    restore_rgb();
    indicator_triggered = false;
  }
}
