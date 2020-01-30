#include "saesh.h"

__attribute__ ((weak))
bool secrets_process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
      case MAKE:
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

    return secrets_process_record_user(keycode, record);
}
