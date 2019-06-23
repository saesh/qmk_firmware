/* Copyright 2019 Danny Nguyen <danny@keeb.io>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// easy to read encoder names
#define LEFT_ENCODER  0
#define RIGHT_ENCODER 1

// layers
#define MEDIA    0
#define SETTINGS 1
#define BROWSER  2
#define DIABLO   3

// tap dance commands
#define CLOSE_TAB C(KC_W)
#define UNDO_CLOSE C(LSFT(KC_T))

#define RELOAD C(LSFT(KC_R))
#define NEW_TAB C(KC_T)
#define NEXT_TAB C(KC_PGDN)
#define PREV_TAB C(KC_PGUP)
#define NETWORK C(LSFT(KC_E))

#define E1M1_DOOM  \
    Q__NOTE(_E3 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_E4 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_D4 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_C4 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_BF3), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_B3 ), \
    Q__NOTE(_C4 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_E4 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_D4 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_C4 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_E3 ), \
    H__NOTE(_BF3),

float e1m1_doom_song[][2] = SONG(QWERTY_SOUND);
float plank_sound[][2] = SONG(PLANCK_SOUND);
float qwerty_sound[][2] = SONG(QWERTY_SOUND);

// tap dance definitions
enum {
  TD_CLOSE_UNDO = 0
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_CLOSE_UNDO] = ACTION_TAP_DANCE_DOUBLE(CLOSE_TAB, UNDO_CLOSE),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MEDIA] = LAYOUT(
           KC_MUTE, MO(SETTINGS),      KC_END, \
        A(KC_LEFT),      KC_MSTP, A(KC_RIGHT), \
           KC_MPRV,      KC_MPLY,     KC_MNXT \
    ),
    [SETTINGS] = LAYOUT(
          RESET,    _______,     _______, \
        _______,    _______,     _______, \
        _______, TG(DIABLO), TG(BROWSER) \
    ),
    [BROWSER] = LAYOUT(
         _______,         TO(SETTINGS), _______, \
        PREV_TAB,            RELOAD,   NEXT_TAB, \
         NETWORK, TD(TD_CLOSE_UNDO),    NEW_TAB \
    ),
    [DIABLO] = LAYOUT(
                    KC_I, TO(SETTINGS),  _______, \
                    KC_1,         KC_2,     KC_3, \
        LSFT_T(KC_SPACE),         KC_Q,     KC_4 \
    )
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == LEFT_ENCODER) {
        if (clockwise) {
          tap_code(KC_VOLU);
        } else {
          tap_code(KC_VOLD);
        }
    }
    else if (index == RIGHT_ENCODER) {
        if (clockwise) {
            tap_code(KC_WH_D);
        } else {
            tap_code(KC_WH_U);
        }
    }
}

uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
    case MEDIA:
        PLAY_SONG(qwerty_sound);
        break;
    case DIABLO:
        PLAY_SONG(e1m1_doom_song);
        break;
    case  BROWSER:
        PLAY_SONG(plank_sound);
        break;
    default:
        break;
    }
  return state;
}

