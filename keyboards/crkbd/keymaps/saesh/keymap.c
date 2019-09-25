#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _I3     1
#define _LOWER  2
#define _RAISE  3
#define _ADJUST 4
#define _GAME   5

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO

#define KC_LOWER LOWER
#define KC_RAISE RAISE

#define KC_RST   RESET          // Reset controller
#define KC_ERMR  EEP_RST        // EEPROM reset

#define KC_LTOG  RGB_TOG
#define KC_LMOD  RGB_MOD
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LSPI  RGB_SPI
#define KC_LSPD  RGB_SPD

#define KC_CTLTB CTL_T(KC_TAB)  // Ctrl+Tab
#define KC_G(x) G(x)            // GUI
#define KC_QUIT SGUI(KC_Q)      // i3 exit program
#define KC_GESC GRAVE_ESC       // Grace Esc

#define KC_WSL G(C(KC_LEFT))    // Cycle to workspace left
#define KC_WSR G(C(KC_RIGHT))   // Cycle to workspace right

#define KC_TG(x) TG(x)
#define KC_LM(l, m) LM(l, m)
#define KC_MO(x) MO(x)

extern uint8_t is_master;

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  GAME
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc(
  //,-----------------------------------------.                ,-----------------------------------------.
       GESC,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLTB,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN,  QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH,  RSFT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                        LM(1, MOD_LGUI), LOWER, SPACE,    ENTER, RAISE,  RALT
                              //`--------------------'  `--------------------'
  ),

  [_I3] = LAYOUT_kc(
  //,-----------------------------------------.                ,-----------------------------------------.
      _____, _____, _____, _____, _____, _____,                  _____, _____,     1,     2,     3,     4,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, _____, _____, _____, _____, _____,                  _____, _____,     5,     6,     7,     8,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, _____, _____, _____, _____, _____,                  _____, _____,    F1,    F2,    F3,    F4,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,    _____, _____,  LALT
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc(
  //,-----------------------------------------.                ,-----------------------------------------.
      XXXXX,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0,   DEL,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLTB, XXXXX, XXXXX,  LBRC,  LCBR,  LPRN,                   LEFT,  DOWN,    UP, RIGHT,   WSL,   WSR,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LALT, XXXXX, XXXXX,  RBRC,  RCBR,  RPRN,                   HOME,  PGDN,  PGUP,   END,  BSLS,   INS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LGUI, LOWER, SPACE,    ENTER, RAISE,  QUIT
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_kc(
  //,-----------------------------------------.                ,-----------------------------------------.
      XXXXX,  EXLM,    AT,  HASH,   DLR,  PERC,                   CIRC,  AMPR,  ASTR,  UNDS,  PLUS,  MINS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLTB, XXXXX, XXXXX, XXXXX,   EQL, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,  PIPE,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LALT, XXXXX, XXXXX, XXXXX,   MINS, UNDS,                   TILD,  XXXXX, XXXXX, XXXXX, BSLS,  RSFT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LGUI, LOWER, SPACE,    ENTER, RAISE, XXXXX
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_kc(
  //,-----------------------------------------.                ,-----------------------------------------.
  TG(_GAME), XXXXX, XXXXX,  ERMR,  RST,  XXXXX,                  XXXXX, XXXXX,  MRWD,  MFFD, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LTOG,  LHUI,  LSAI,  LVAI,  LSPI, XXXXX,                  XXXXX,  MPLY,  MPRV,  MNXT, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LMOD,  LHUD,  LSAD,  LVAD,  LSPD, XXXXX,                  XXXXX, XXXXX,  VOLD,  VOLU,  MUTE, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  XXXXX, LOWER, XXXXX,    XXXXX, RAISE, XXXXX
                              //`--------------------'  `--------------------'
  ),

  // Apex Legends
  [_GAME] = LAYOUT_kc(
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,     Q,     W,     E,     R,     T,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     A,     S,     D,     F,     G,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LCTL,     Z,     X,     C,     V,     B,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                      M,     J , SPACE,   TG(_GAME), XXXXX, XXXXX
                              //`--------------------'  `--------------------'
  )
};

void matrix_init_user(void) {
    #ifdef SSD1306OLED
        // turns on the display
        iota_gfx_init(!has_usb());
    #endif
}

void matrix_scan_user(void) {
    #ifdef SSD1306OLED
        // update display continously
        iota_gfx_task();
    #endif
}

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
  }
  return true;
}

void suspend_power_down_user(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_suspend_state(true);
#endif
}

void suspend_wakeup_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_suspend_state(false);
#endif
}

#ifdef SSD1306OLED
char matrix_line_str[24];
const char *read_layer_state(void) {
  uint8_t layer = biton32(layer_state);

  strcpy(matrix_line_str, "Layer: ");

  switch (layer)
  {
    case _QWERTY:
      strcat(matrix_line_str, "Default");
      break;
    case _I3:
      strcat(matrix_line_str, "i3");
      break;
    case _LOWER:
      strcat(matrix_line_str, "Lower");
      break;
    case _RAISE:
      strcat(matrix_line_str, "Raise");
      break;
    case _ADJUST:
      strcat(matrix_line_str, "Adjust");
      break;
    case _GAME:
      strcat(matrix_line_str, "Game");
      break;
    default:
      sprintf(matrix_line_str + strlen(matrix_line_str), "Unknown (%d)", layer);
  }

  return matrix_line_str;
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    matrix_write_ln(matrix, read_layer_state());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif
