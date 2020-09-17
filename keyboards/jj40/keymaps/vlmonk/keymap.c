/* Copyright 2019
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

enum layers {
  _QWERTY = 0,
  _SYMB,
  _NAV,
  _NUM
};

// tap dance

enum tap_dance {
  TD_DOUBLE_ALT,
};

static bool alt_pressed = false;
void double_alt_done(qk_tap_dance_state_t *state, void *user_data);
void double_alt_reset(qk_tap_dance_state_t *state, void *user_data);

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_DOUBLE_ALT] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, double_alt_done, double_alt_reset, 200),
};


// ctrl <- / ctrl ->
#define KC_CT_L C(KC_LEFT)
#define KC_CT_R C(KC_RIGHT)

// volume keycodes
#define VL_MUTE KC__MUTE
#define VL_UP KC__VOLUP
#define VL_DOWN KC__VOLDOWN

// ctrl / esc button
#define KC_CESC MT(MOD_LCTL, KC_ESC)

// more custom keys
#define KC_FKEY LT(_SYMB, KC_F)
#define KC_JKEY LT(_SYMB, KC_J)
#define KC_NAV MO(_NAV)
#define KC_DNUM LT(_NUM, KC_D)
#define KC_DALT TD(TD_DOUBLE_ALT)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT_ortho_4x12( \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,  \
  KC_CESC, KC_A,    KC_S,    KC_DNUM, KC_FKEY, KC_G,    KC_H,    KC_JKEY, KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
  XXXXXXX, XXXXXXX, XXXXXXX, KC_LGUI, KC_BSPC, KC_NAV,  KC_ENT,  KC_SPC,  KC_DALT, XXXXXXX, XXXXXXX, XXXXXXX  \
),

[_SYMB] = LAYOUT_ortho_4x12( \
  _______, KC_GRV,  KC_AT,   KC_PIPE, KC_LCBR, KC_RCBR, KC_BSLS, KC_ASTR, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
  _______, KC_DQUO, KC_EXLM, KC_DLR,  KC_LPRN, KC_RPRN, KC_MINS, KC_AMPR, KC_HASH, XXXXXXX, KC_COLN, _______, \
  _______, KC_QUOT, KC_TILD, KC_PERC, KC_LBRC, KC_RBRC, KC_UNDS, KC_CIRC, KC_LABK, KC_RABK, XXXXXXX, _______, \
  XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX  \
 ),

[_NAV] = LAYOUT_ortho_4x12( \
  RESET,   RGB_TOG, RGB_MOD, VL_MUTE, VL_DOWN, VL_UP,   _______, _______, _______, _______, _______, DEBUG,   \
  KC_LCTL, RGB_SAI, RGB_VAI, RGB_SPI, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_UP,   _______, \
  KC_LSFT, RGB_SAD, RGB_VAD, RGB_SPD, KC_CT_L, KC_CT_R, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, \
  XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, KC_F20,  KC_F21,  _______, XXXXXXX, XXXXXXX, XXXXXXX  \
),

[_NUM] = LAYOUT_ortho_4x12( \
  _______, _______, _______, _______, _______, _______, KC_PDOT, KC_7,    KC_8,    KC_9,    KC_PPLS, _______, \
  _______, _______, _______, _______, _______, _______, KC_MINS, KC_4,    KC_5,    KC_6,    KC_PMNS, _______, \
  _______, _______, _______, _______, _______, _______, KC_UNDS, KC_1,    KC_2,    KC_3,    KC_PSLS, KC_PAST, \
  XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______, KC_0,    XXXXXXX, XXXXXXX, XXXXXXX  \
)
};


/*
[_blank] = LAYOUT_planck_mit( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
),

*/


// tap-dance functions

void double_alt_done(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 2 && !state->pressed) {
    register_mods(MOD_BIT(KC_RALT));
    register_code(KC_SPC);

    unregister_code(KC_SPC);
    unregister_mods(MOD_BIT(KC_RALT));
  } else if (state->pressed) {
    alt_pressed = true;
    register_mods(MOD_BIT(KC_RALT));
  }
}

void double_alt_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (alt_pressed) {
    unregister_mods(MOD_BIT(KC_RALT));
  }
}
