#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3
};

int cur_dance (qk_tap_dance_state_t *state);

/* void left_mod_finished(qk_tap_dance_state_t *state, void *user_data); */
/* void left_mod_reset(qk_tap_dance_state_t *state, void *user_data); */

/* void right_mod_finished(qk_tap_dance_state_t *state, void *user_data); */
/* void right_mod_reset(qk_tap_dance_state_t *state, void *user_data); */

void double_alt_done(qk_tap_dance_state_t *state, void *user_data);
void double_alt_reset(qk_tap_dance_state_t *state, void *user_data);
static bool alt_pressed = false;

//Tap Dance Declarations
enum {
  TD_LEFT_BR = 0,
  TD_RGHT_BR,
  /* TD_LEFT_MOD, */
  /* TD_RIGHT_MOD, */
  TD_DOUBLE_ALT
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  // single tap for '[', double tap for '{'
  [TD_LEFT_BR]  = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_LCBR),
  // single tap for ']', double tap for '}'
  [TD_RGHT_BR]  = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, KC_RCBR),
  /* [TD_LEFT_MOD] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, left_mod_finished, left_mod_reset, 200), */
  /* [TD_RIGHT_MOD] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, right_mod_finished, right_mod_reset, 200) */
// Other declarations would go here, separated by commas, if you have them
  [TD_DOUBLE_ALT] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, double_alt_done, double_alt_reset, 200)
};


enum LAYERS {
  _QWERTY,
  _SYMB_L,
  _SYMB_R,
  _NAV,
  _NUM,
  _CMD_NUM
};

#define MY_LBR  TD(TD_LEFT_BR)
#define MY_RBR  TD(TD_RGHT_BR)

// left mod switch, tap dance to _SYM layer
/* #define MY_LMD   TD(TD_LEFT_MOD) */
#define MY_SYM   OSL(_SYMB_L)
#define MY_NAV   OSL(_NAV)
#define MY_NUM   TG(_NUM)

#define KC_VUP KC__VOLUP
#define KC_VDW KC__VOLDOWN
#define KC_VMT KC__MUTE

// hold 'D' to activate numpad layer
#define MY_DNM LT(_NUM, KC_D)
// hold 'W' to activate numpad layer + command
#define MY_WNM LT(_CMD_NUM, KC_W)

// hold 'J' / 'F' to activate symbol layer
#define KC_J_SYM LT(_SYMB_L, KC_J)
#define KC_F_SYM LT(_SYMB_R, KC_F)


#define KC_DALT TD(TD_DOUBLE_ALT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     RGB_TOG ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,                                            KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB  ,KC_Q    ,MY_WNM  ,KC_E    ,KC_R    ,KC_T    ,RGB_M_T ,                          MY_NUM  ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_EQL  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_ESC  ,KC_A    ,KC_S    ,MY_DNM  ,KC_F_SYM,KC_G    ,MY_LBR  ,                          MY_RBR  ,KC_H    ,KC_J_SYM,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,KC_PGUP ,KC_PGDN ,        KC_HOME ,KC_END  ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSFT ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_LCTL ,KC_NO   ,KC_NO   ,KC_LALT ,     KC_RGUI ,    KC_BSPC ,MY_NAV  ,        KC_ENT  ,KC_SPC  ,    KC_DALT ,     KC_RALT ,KC_NO   ,KC_NO   ,KC_RCTL
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_SYMB_L] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_TRNS ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                             _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_GRV  ,KC_AT   ,KC_PIPE ,KC_LCBR ,KC_RCBR ,KC_TRNS ,                           _______, _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_DQUO ,KC_EXLM ,KC_DLR  ,KC_LPRN ,KC_RPRN ,KC_TRNS ,                           _______, _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_QUOT ,KC_TILD ,KC_PERC ,KC_LBRC ,KC_RBRC ,KC_TRNS ,KC_TRNS,          _______, _______, _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,     KC_TRNS ,    KC_TRNS ,KC_TRNS ,         _______, _______,     _______,      _______, _______, _______, _______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),
  [_SYMB_R] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
      _______, _______, _______, _______, _______, _______,                                            KC_F6   ,KC_F7   ,KC_F8   ,KC_F9    ,KC_F10  ,KC_NO  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      _______, _______, _______, _______, _______, _______, _______,                          KC_TRNS ,KC_BSLS ,KC_ASTR ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      _______, _______, _______, _______, _______, _______, _______,                          KC_TRNS ,KC_MINS ,KC_AMPR  ,KC_HASH ,KC_NO   ,KC_NO   ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      _______, _______, _______, _______, _______, _______, _______, _______,         KC_TRNS ,KC_TRNS ,KC_UNDS ,KC_CIRC ,KC_CIRC ,KC_NO   ,KC_NO   ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
      _______, _______, _______, _______,      _______,     _______, _______,        KC_TRNS ,KC_TRNS ,    KC_TRNS ,     KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),
  [_NAV] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,                                            KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,RESET   ,                          KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_NO   ,KC_NO   ,KC_VMT  ,KC_VDW  ,KC_VUP  ,KC_NO   ,                          KC_NO   ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT ,KC_NO   ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,        KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_NO   ,KC_NO   ,KC_TRNS ,     KC_TRNS ,    KC_TRNS ,KC_TRNS ,        KC_TRNS ,KC_TRNS ,    KC_NO   ,     KC_NO   ,KC_NO   ,KC_NO   ,KC_TRNS
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_NUM] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,                                            KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,                          MY_NUM  ,KC_PDOT ,KC_7    ,KC_8    ,KC_9    ,KC_PPLS ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     MY_NUM  ,KC_NO   ,KC_NO   ,MY_DNM  ,KC_NO   ,KC_NO   ,KC_NO   ,                          KC_NO   ,KC_MINS ,KC_4    ,KC_5    ,KC_6    ,KC_PMNS ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,        KC_NO   ,KC_NO   ,KC_UNDS ,KC_1    ,KC_2    ,KC_3    ,KC_PSLS ,KC_PAST ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,     KC_NO   ,    KC_BSPC ,KC_NO   ,        KC_ENT  ,KC_SPC  ,    KC_0    ,     KC_NO   ,KC_NO   ,KC_NO   ,KC_NO
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_CMD_NUM] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,                                            KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO   ,KC_NO   ,MY_WNM  ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,                          MY_NUM  ,KC_PDOT ,G(KC_7) ,G(KC_8) ,G(KC_9) ,KC_PPLS ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     MY_NUM  ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,                          KC_NO   ,KC_MINS ,G(KC_4) ,G(KC_5) ,G(KC_6) ,KC_PMNS ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,        KC_NO   ,KC_NO   ,KC_UNDS ,G(KC_1) ,G(KC_2) ,G(KC_3) ,KC_PSLS ,KC_PAST ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,     KC_NO   ,    KC_BSPC ,KC_NO   ,        KC_ENT  ,KC_SPC  ,    G(KC_0) ,     KC_NO   ,KC_NO   ,KC_NO   ,KC_NO
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  )
};



int cur_dance(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed) {
      return SINGLE_TAP;
    } else {
      return SINGLE_HOLD;
    }
  } else if (state->count == 2) {
    return DOUBLE_TAP;
  } else  {
    return 8;
  }
}

/* static tap left_mod_tap = { */
/*   .is_press_action = true, */
/*   .state = 0 */
/* }; */

/* static tap right_mod_tap = { */
/*   .is_press_action = true, */
/*   .state = 0 */
/* }; */

/* void left_mod_finished(qk_tap_dance_state_t *state, void *user_data) { */
/*   left_mod_tap.state = cur_dance(state); */
/*   switch (left_mod_tap.state) { */
/*     case SINGLE_TAP: */
/*       set_oneshot_layer(_SYMB, ONESHOT_START); */
/*       clear_oneshot_layer_state(ONESHOT_PRESSED); */
/*       break; */
/*     case SINGLE_HOLD: */
/*       layer_on(_SYMB); */
/*       break; */
/*     case DOUBLE_TAP: */
/*       layer_on(_SYMB); */
/*       break; */
/*   } */
/* } */

/* void left_mod_reset(qk_tap_dance_state_t *state, void *user_data) { */
/*   switch (left_mod_tap.state) { */
/*     case SINGLE_HOLD: */
/*       layer_off(_SYMB); */
/*       break; */
/*   } */
/*   left_mod_tap.state = 0; */
/* } */

/* void right_mod_finished(qk_tap_dance_state_t *state, void *user_data) { */
/*   right_mod_tap.state = cur_dance(state); */
/*   switch (right_mod_tap.state) { */
/*     case SINGLE_TAP: */
/*       set_oneshot_layer(_NAV, ONESHOT_START); */
/*       clear_oneshot_layer_state(ONESHOT_PRESSED); */
/*       break; */
/*     case SINGLE_HOLD: */
/*       layer_on(_NAV); */
/*       break; */
/*     case DOUBLE_TAP: */
/*       layer_on(_NAV); */
/*       break; */
/*   } */
/* } */

/* void right_mod_reset(qk_tap_dance_state_t *state, void *user_data) { */
/*   switch (right_mod_tap.state) { */
/*     case SINGLE_HOLD: */
/*       layer_off(_NAV); */
/*       break; */
/*   } */
/*   right_mod_tap.state = 0; */
/* } */


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
