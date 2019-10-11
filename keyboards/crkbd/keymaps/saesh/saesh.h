#pragma once

#include "quantum.h"

#define _QWERTY 0
#define _LOWER  1
#define _RAISE  2
#define _ADJUST 3

enum custom_keycodes {
  KC_TOGGLE_OLED = SAFE_RANGE,
  KC_MAKE,
  KC_SECRET_1,
  KC_SECRET_2,
  KC_SECRET_3,
  KC_SECRET_4,
  KC_SECRET_5
};