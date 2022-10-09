#pragma once

#include "quantum.h"
#include "version.h"

enum tap_dancers {
  TD_GRAVE = 0,
  TD_QUIT  = 1,
};

enum user_custom_keys {
  KC_MAKE = SAFE_RANGE,
  KC_SECRET_1,
  KC_SECRET_2,
  KC_SECRET_3,
  KC_SECRET_4,
  KC_SECRET_5,
  NEW_SAFE_RANGE
};

#define CK_EGT   TD(TD_GRAVE) // escape, grave, tilde
#define KC_QIT   TD(TD_QUIT)  // gui+q on double q

void matrix_init_user(void);
void matrix_init_keymap(void);
// uint32_t layer_state_set_user(uint32_t state);
uint32_t layer_state_set_keymap(uint32_t state);
void led_set_user(uint8_t usb_led);
void led_set_keymap(uint8_t usb_led);