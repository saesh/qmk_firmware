#undef RGBLED_NUM
#define RGBLED_NUM 4

#define RGB_DI_PIN F4
#ifdef RGB_DI_PIN
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_ANIMATIONS
#endif

#define TAP_CODE_DELAY 5