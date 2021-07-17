#include "saesh.h"

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

__attribute__ ((weak))
bool secrets_process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

__attribute__ ((weak))
void matrix_init_keymap() {}

void matrix_init_user(void) {
  matrix_init_keymap();
}

__attribute__ ((weak))
uint32_t layer_state_set_keymap(uint32_t state) {
  return state;
}

uint32_t layer_state_set_user(uint32_t state) {
  return layer_state_set_keymap(state);
}

__attribute__ ((weak))
void led_set_keymap(uint8_t usb_led) {}

void led_set_user(uint8_t usb_led) {
  led_set_keymap(usb_led);
}

/*

Build firmware locally or with Docker, flash optionally

Key pressed: build locally
Key pressed + ctrl: build with Docker
Key pressed [ctrl|none] + shift: reset and flash

*/
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
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

        send_string_with_delay_P(PSTR(SS_TAP(X_ENTER)), TAP_CODE_DELAY);

        if (mods & MOD_MASK_SHIFT) {
          reset_keyboard();
        }
      }
      break;
    }

    return secrets_process_record_user(keycode, record) && 
           process_record_keymap(keycode, record);
}

void tap_dance_esc_grave_tilde(qk_tap_dance_state_t *state, void *user_data) {
  switch(state->count) {
  case 1:
    tap_code(KC_ESC);
    break;
  case 2:
    SEND_STRING("`");
    break;
  case 3:
    SEND_STRING("~");
    break;
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_GRAVE] = ACTION_TAP_DANCE_FN(tap_dance_esc_grave_tilde),
  [TD_QUIT] = ACTION_TAP_DANCE_DOUBLE(KC_Q, LGUI(KC_Q)),
};