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

void left_mod_finished(qk_tap_dance_state_t *state, void *user_data);
void left_mod_reset(qk_tap_dance_state_t *state, void *user_data);

void right_mod_finished(qk_tap_dance_state_t *state, void *user_data);
void right_mod_reset(qk_tap_dance_state_t *state, void *user_data);

//Tap Dance Declarations
enum {
  TD_LEFT_BR = 0,
  TD_RGHT_BR,
  TD_LEFT_MOD,
  TD_RIGHT_MOD
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  // single tap for '[', double tap for '{'
  [TD_LEFT_BR]  = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_LCBR),
  // single tap for ']', double tap for '}'
  [TD_RGHT_BR]  = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, KC_RCBR),
  [TD_LEFT_MOD] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, left_mod_finished, left_mod_reset, 200),
  [TD_RIGHT_MOD] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, right_mod_finished, right_mod_reset, 200)
// Other declarations would go here, separated by commas, if you have them
};



#define _QWERTY 0
#define _SYMB 1
#define _NAV 2

#define LT2_GRV LT(_NAV,KC_GRV)
#define LT2_MIN LT(_NAV,KC_MINS)
#define LT2_PU  LT(_NAV,KC_PGUP)
#define LT2_END LT(_NAV,KC_END)
#define LNV_PLS LT(_NAV,KC_PPLS)

#define AL_PAST LALT_T(KC_PAST)
#define AL_LEFT RALT_T(KC_LEFT)
#define CTL_R   LCTL_T(KC_RGHT)

#define MY_LBR  TD(TD_LEFT_BR)
#define MY_RBR  TD(TD_RGHT_BR)

// custom spacebar with command on tap
#define MY_SPC   MT(MOD_RGUI, KC_SPC)

// left mod switch, tap dance to _SYM layer
#define MY_LMD   TD(TD_LEFT_MOD)

// right mod switch, tap dance to _NAV layer
#define MY_RMD   TD(TD_RIGHT_MOD)

// disable _SYMB layer
#define NO_SYM   TG(_SYMB)

// disable _NAV layer
#define NO_NAV   TG(_NAV)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     LT2_GRV ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                                            KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,LT2_MIN ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,KC_NO   ,                          KC_NO   ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_EQL  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_ESC  ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,MY_LBR  ,                          MY_RBR  ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSPO ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,LT2_PU  ,KC_PGDN ,        KC_HOME ,LT2_END ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSPC ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_LCTL ,LNV_PLS ,KC_PMNS ,AL_PAST ,     MY_RMD  ,    KC_BSPC ,KC_LCMD ,        KC_ENT  ,MY_SPC  ,    MY_LMD  ,     AL_LEFT ,KC_DOWN ,KC_UP   ,CTL_R
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_SYMB] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_TRNS ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_F6   ,KC_F7   ,KC_F8   ,KC_F9    ,KC_F10  ,KC_NO  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_EXLM ,KC_AT   ,KC_LCBR ,KC_RCBR ,KC_PIPE ,KC_TRNS ,                          KC_TRNS ,KC_BSLS ,KC_P7   ,KC_P8    ,KC_P9  ,KC_NO   ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_HASH  ,KC_DLR ,KC_LBRC ,KC_RBRC ,KC_GRV  ,KC_TRNS ,                          KC_TRNS ,KC_NO   ,KC_P4   ,KC_P5   ,KC_P6   ,KC_NO   ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_PERC ,KC_CIRC ,KC_LPRN ,KC_RPRN ,KC_TILD ,KC_TRNS ,KC_TRNS,         KC_TRNS ,KC_TRNS ,KC_NO   ,KC_P1   ,KC_P2   ,KC_P3   ,KC_NO   ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,     NO_NAV  ,    KC_TRNS ,KC_TRNS ,        KC_TRNS ,KC_TRNS ,    NO_SYM  ,     KC_P0   ,KC_PDOT ,KC_NO   ,KC_NO
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),
  [_NAV]=LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,                                            KC_TRNS ,KC_TRNS,KC_TRNS  ,KC_TRNS ,KC_TRNS ,KC_TRNS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO   ,KC_NO   ,KC_MS_U ,KC_NO   ,KC_WH_U ,KC_NO   ,KC_TRNS ,                          KC_TRNS ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO   ,KC_MS_L ,KC_MS_D ,KC_MS_R ,KC_WH_D ,KC_NO   ,KC_TRNS ,                          KC_TRNS ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT ,KC_NO   ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_TRNS ,KC_TRNS ,        KC_TRNS ,KC_TRNS ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_TRNS ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,     KC_TRNS ,    KC_TRNS ,KC_TRNS ,        KC_TRNS ,KC_TRNS ,    KC_TRNS ,     KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
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
  } else {
    return 8;
  }
}

static tap left_mod_tap = {
  .is_press_action = true,
  .state = 0
};

static tap right_mod_tap = {
  .is_press_action = true,
  .state = 0
};

void left_mod_finished(qk_tap_dance_state_t *state, void *user_data) {
  left_mod_tap.state = cur_dance(state);
  switch (left_mod_tap.state) {
    case SINGLE_TAP:
      set_oneshot_layer(_SYMB, ONESHOT_START);
      clear_oneshot_layer_state(ONESHOT_PRESSED);
      break;
    case SINGLE_HOLD:
      layer_on(_SYMB);
      break;
    case DOUBLE_TAP:
      layer_on(_SYMB);
      break;
  }
}

void left_mod_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (left_mod_tap.state) {
    case SINGLE_HOLD:
      layer_off(_SYMB);
      break;
  }
  left_mod_tap.state = 0;
}

void right_mod_finished(qk_tap_dance_state_t *state, void *user_data) {
  right_mod_tap.state = cur_dance(state);
  switch (right_mod_tap.state) {
    case SINGLE_TAP:
      set_oneshot_layer(_NAV, ONESHOT_START);
      clear_oneshot_layer_state(ONESHOT_PRESSED);
      break;
    case SINGLE_HOLD:
      layer_on(_NAV);
      break;
    case DOUBLE_TAP:
      layer_on(_NAV);
      break;
  }
}

void right_mod_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (right_mod_tap.state) {
    case SINGLE_HOLD:
      layer_off(_NAV);
      break;
  }
  right_mod_tap.state = 0;
}
