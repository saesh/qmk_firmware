#include "tapdances.h"
#include "quantum.h" // KC_CAPS

qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Shift, twice for Caps Lock
  [SHFT_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS)
};