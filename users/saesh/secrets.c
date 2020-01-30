#include "saesh.h"

#if (__has_include("secrets.h") && !defined(NO_SECRETS))
#include "secrets.h"
#else
static const char * const secrets[] = {
  "",
  "",
  "",
  "",
  ""
};
#endif

bool secrets_process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_SECRET_1 ... KC_SECRET_5:
      if (!record->event.pressed) {
        send_string(secrets[keycode - KC_SECRET_1]);
      }
      return false;
  }

  return true;
}