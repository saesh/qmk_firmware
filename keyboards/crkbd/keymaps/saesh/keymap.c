#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _LOWER  1
#define _RAISE  2
#define _ADJUST 3

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO

#define KC_LOWER LOWER
#define KC_RAISE RAISE

#define KC_RST   RESET          // Reset controller
#define KC_EPRM  EPRM           // EPROM reset

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
#define KC_TD(x) TD(x)          // Tap Dance
#define KC_G(x) G(x)            // GUI
#define KC_SGUI(x) SGUI(x)      // Shift+Gui

#define KC_M1 SGUI(KC_1)        // Move to first workspace
#define KC_M2 SGUI(KC_2)
#define KC_M3 SGUI(KC_3)
#define KC_M4 SGUI(KC_4)
#define KC_WSL G(C(KC_LEFT))    // Cycle to workspace left
#define KC_WSR G(C(KC_RIGHT))   // Cycle to workspace right

extern uint8_t is_master;

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  EPRM
};

enum {
  GRVTIL = 0,
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [GRVTIL] = ACTION_TAP_DANCE_DOUBLE(KC_GRV, KC_TILD)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc(
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLTB,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN,  QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LALT,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH,  RSFT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LGUI, LOWER, SPACE,    ENTER, RAISE,  RALT
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc(
  //,-----------------------------------------.                ,-----------------------------------------.
 TD(GRVTIL), XXXXX, XXXXX, XXXXX,  MINS,  LBRC,                   RBRC,     7,     8,     9,   INS,   DEL,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLTB, XXXXX, XXXXX, XXXXX,   EQL,  LPRN,                   RPRN,     4,     5,     6,   WSL,   WSR,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LALT, XXXXX, XXXXX, XXXXX,  UNDS,  LCBR,                   RCBR,     1,     2,     3, XXXXX,  RSFT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LGUI, LOWER, SPACE,    ENTER, RAISE,     0
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_kc(
  //,-----------------------------------------.                ,-----------------------------------------.
 TD(GRVTIL),  EXLM,    AT,  HASH,   DLR,  PERC,                   CIRC,  AMPR,  ASTR,  UNDS,  PLUS,  MINS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLTB,     M1,   M2,    M3,    M4, XXXXX,                   LEFT,  DOWN,    UP, RIGHT, XXXXX,  PIPE,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LALT, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                   HOME,  PGDN,  PGUP,   END,  BSLS,  RSFT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LGUI, LOWER, SPACE,    ENTER, RAISE, SGUI(KC_Q)
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_kc(
  //,-----------------------------------------.                ,-----------------------------------------.
      XXXXX, XXXXX, XXXXX,  EPRM, XXXXX,   RST,                  XXXXX, XXXXX,  MRWD,  MFFD, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LTOG,  LHUI,  LSAI,  LVAI,  LSPI, XXXXX,                  XXXXX,  MPLY,  MPRV,  MNXT, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LMOD,  LHUD,  LSAD,  LVAD,  LSPD, XXXXX,                  XXXXX, XXXXX,  VOLD,  VOLU,  MUTE, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LALT, LOWER, SPACE,    ENTER, RAISE,  RALT
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
     case EPRM:
        if (record->event.pressed) {
            eeconfig_init();
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
const char *read_layer_state(void);

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
