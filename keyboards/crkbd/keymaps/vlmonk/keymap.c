#include QMK_KEYBOARD_H
#include <print.h>

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
//
enum layers {
  _QWERTY,
  _SYMB_L,
  _SYMB_R,
  _NAV,
  _NUM,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  BACKLIT,
  RGBRST
};

enum tap_dance {
  TD_DOUBLE_ALT,
  TD_WNUM,
  TD_LSHIFT,
  TD_RSHIFT,
  TD_JKEY,
  TD_FKEY
};


enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  UNKNOWN_TAPHOLD = 5
};

int cur_dance(qk_tap_dance_state_t *state);
int i_state;

static bool alt_pressed = false;
void double_alt_done(qk_tap_dance_state_t *state, void *user_data);
void double_alt_reset(qk_tap_dance_state_t *state, void *user_data);

/* static int w_tap_state = 0; */
void w_tap(qk_tap_dance_state_t *state, void *user_data);
void w_finished(qk_tap_dance_state_t *state, void *user_data);
void w_reset(qk_tap_dance_state_t *state, void *user_data);

void j_tap(qk_tap_dance_state_t *state, void *user_data);
void j_finished(qk_tap_dance_state_t *state, void *user_data);
void j_reset(qk_tap_dance_state_t *state, void *user_data);

void f_tap(qk_tap_dance_state_t *state, void *user_data);
void f_finished(qk_tap_dance_state_t *state, void *user_data);
void f_reset(qk_tap_dance_state_t *state, void *user_data);


//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_DOUBLE_ALT] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, double_alt_done, double_alt_reset, 200),
  [TD_WNUM] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(w_tap, w_finished, w_reset, 200),
  [TD_JKEY] = ACTION_TAP_DANCE_FN_ADVANCED(j_tap, j_finished, j_reset),
  [TD_FKEY] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(f_tap, f_finished, f_reset, 200),
};


// custom keys
#define KC_NAV MO(_NAV)
#define KC_DNUM LT(_NUM, KC_D)
#define KC_WNUM TD(TD_WNUM)
#define KC_DALT TD(TD_DOUBLE_ALT)
#define KC_FKEY TD(TD_FKEY)
#define KC_JKEY TD(TD_JKEY)

// ctrl / esc button
#define KC_CESC MT(MOD_LCTL, KC_ESC)

// ctrl <- / ctrl ->
#define KC_CT_L C(KC_LEFT)
#define KC_CT_R C(KC_RIGHT)

// volume keycodes
#define VL_MUTE KC__MUTE
#define VL_UP KC__VOLUP
#define VL_DOWN KC__VOLDOWN

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,                     KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_EQL  ,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_CESC ,KC_A    ,KC_S    ,KC_DNUM ,KC_FKEY ,KC_G    ,                     KC_H    ,KC_JKEY ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,                     KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_LGUI ,KC_BSPC ,KC_NAV  ,   KC_ENT  ,KC_SPC  ,KC_DALT \
                                      //`--------------------------'  `--------------------------'
  ),

  [_SYMB_L] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     _______ ,KC_GRV  ,KC_AT   ,KC_PIPE ,KC_LCBR ,KC_RCBR ,                     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______ ,KC_DQUO ,KC_EXLM ,KC_DLR  ,KC_LPRN ,KC_RPRN ,                     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______ ,KC_QUOT ,KC_TILD ,KC_PERC ,KC_LBRC ,KC_RBRC ,                     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         _______ ,_______ ,_______ ,   _______ ,_______ ,_______ \
                                      //`--------------------------'  `--------------------------'
  ),

  [_SYMB_R] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                     KC_BSLS ,KC_ASTR ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                     KC_MINS ,KC_AMPR ,KC_HASH ,XXXXXXX ,KC_COLN ,_______ ,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                     KC_UNDS ,KC_CIRC ,KC_LABK ,KC_RABK  ,XXXXXXX ,_______ ,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         _______ ,_______ ,_______ ,   _______ ,_______ ,_______ \
                                      //`--------------------------'  `--------------------------'
  ),

  [_NAV] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     RESET   ,RGB_TOG ,RGB_MOD ,VL_MUTE ,VL_DOWN ,VL_UP   ,                     _______ ,_______ ,_______ ,_______ ,_______ ,DEBUG   ,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_LCTL ,RGB_SAI ,RGB_VAI ,RGB_SPI ,_______ ,_______ ,                     KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT ,KC_UP   ,_______ ,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_LSFT ,RGB_SAD ,RGB_VAD ,RGB_SPD ,KC_CT_L ,KC_CT_R ,                     _______ ,_______ ,_______ ,KC_LEFT ,KC_DOWN ,KC_RGHT ,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         _______ ,_______ ,_______ ,   KC_F20  ,KC_F21  ,_______ \
                                      //`--------------------------'  `--------------------------'
  ),

  [_NUM] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                     KC_PDOT ,KC_7    ,KC_8    ,KC_9    ,KC_PPLS ,_______ ,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                     KC_MINS ,KC_4    ,KC_5    ,KC_6    ,KC_PMNS ,_______ ,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                     KC_UNDS ,KC_1    ,KC_2    ,KC_3    ,KC_PSLS ,KC_PAST ,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         _______ ,_______ ,_______ ,   _______ ,_______ ,KC_0    \
                                      //`--------------------------'  `--------------------------'
  ),
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    /* matrix_write_ln(matrix, read_keylog()); */
    //matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
    /* matrix_write_ln(matrix, read_rgb_info()); */
  } else {
    matrix_write(matrix, read_logo());
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
#endif//SSD1306OLED

enum {
  COM_NONE,
  COM_ONE,
  COM_TWO
};


struct remember_t {
  keypos_t first;
  keypos_t last;
  uint8_t step;
} remember = { .step = COM_NONE, .first = { .col = 0, .row = 0 }, .last = { .col = 0, .row = 0 } };

/* remember.step = COM_NONE; */

uint16_t qwerty_key(keypos_t *key) {
  uint16_t original = keymap_key_to_keycode(_QWERTY, *key);
  switch (original) {
    case KC_FKEY:
      return KC_F;
    case KC_JKEY:
      return KC_J;
    default:
      return original;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    dprintf("process_record_user: keycode %d pressed at (%d / %d)\n", keycode, record->event.key.row, record->event.key.col);
  } else {
    dprintf("process_record_user: keycode %d released\n", keycode);
  }

  uint8_t layer = biton32(layer_state);

  switch (remember.step) {
    case COM_NONE:
      if (record->event.pressed && (keycode == KC_FKEY || keycode == KC_JKEY)) {
        dprintf("OK, step one detected, remember %d at (%d / %d)\n", keycode, record->event.key.row, record->event.key.col);
        remember.step = COM_ONE;
        remember.first.col = record->event.key.col;
        remember.first.row = record->event.key.row;
      }
      break;
    case COM_ONE:
      if (record->event.pressed) {
        dprintf("OK, step two detected, remember %d\n", keycode);
        remember.last.col = record->event.key.col;
        remember.last.row = record->event.key.row;
        remember.step = COM_TWO;
        return false;
      } else {
        remember.step = COM_NONE;
      }

      break;
    case COM_TWO:
      if (record->event.pressed) {
        dprintf("OK, step three, press %d\n", keycode);
        register_code16(keymap_key_to_keycode(layer, remember.last));
      } else {
        if (remember.first.col == record->event.key.col && remember.first.row == record->event.key.row) {
          dprintf("Variant 1\n");
          tap_code16(qwerty_key(&remember.first));
          tap_code16(qwerty_key(&remember.last));
          /* register_code16(keymap_key_to_keycode(layer, remember.last)); */
        /* } else if (remember.row == record->event.key.row && remember.col == record->event.key.col) { */
        /*   dprintf("Variant 2 layer: %d, cc: %d\n", layer, keymap_key_to_keycode(layer, pos)); */
        /*   register_code16(keymap_key_to_keycode(layer, pos)); */
        /*   unregister_code16(keymap_key_to_keycode(layer, pos)); */
        /*   remember.step = COM_NONE; */
        /*   return false; */
        } else {
          dprintf("Variant 3\n");
          register_code16(keymap_key_to_keycode(layer, remember.last));
        }
      }

      remember.step = COM_NONE;
      break;
  }

  return true;
}

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

void w_tap(qk_tap_dance_state_t *state, void *user_data) {
  state->finished = true;
  dprint("w_tap\n");
}

void w_reset(qk_tap_dance_state_t *state, void *user_data) {
  dprint("w_reset\n");
}

void w_finished(qk_tap_dance_state_t *state, void *user_data) {
  dprint("w_finished\n");
}

int cur_dance(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->pressed) {
      return SINGLE_HOLD;
    } else {
      return SINGLE_TAP;
    }
  } else if (state->count == 2) {
    if (state->pressed) {
      return DOUBLE_HOLD;
    } else {
      return DOUBLE_TAP;
    }
  } else  {
    return UNKNOWN_TAPHOLD;
  }
}

enum {
  J_NONE,
  J_LAYER,
  J_HOLD
};

int j_status = J_NONE;

void j_tap(qk_tap_dance_state_t *state, void *user_data) {
  dprintf("j_tap, count: %d\n", state->count);

  if (state->count == 1) {
    layer_on(_SYMB_L);
    j_status = J_LAYER;
  } else if (state->count == 2) {
    layer_off(_SYMB_L);
    register_code(KC_J);
    unregister_code(KC_J);
    register_code(KC_J);
    j_status = J_HOLD;
  } else {
    unregister_code(KC_J);
    register_code(KC_J);
  }
}

void j_finished(qk_tap_dance_state_t *state, void *user_data) {
  dprintf("j_finished, count: %d, pressed: %d\n", state->count, state->pressed);

  if (j_status == J_LAYER && !state->pressed) {
    register_code(KC_J);
    unregister_code(KC_J);
  }
}

void j_reset(qk_tap_dance_state_t *state, void *user_data) {
  dprintf("j_reset, count: %d, pressed: %d\n", state->count, state->pressed);

  switch (j_status) {
    case J_LAYER:
      layer_off(_SYMB_L);
      break;
    case J_HOLD:
      unregister_code(KC_J);
      break;
  }

  j_status = J_NONE;
}

enum {
  F_NONE,
  F_LAYER,
  F_HOLD
};

int f_status = F_NONE;

void f_tap(qk_tap_dance_state_t *state, void *user_data) {
  dprintf("f_tap, count: %d\n", state->count);

  if (state->count == 1) {
    layer_on(_SYMB_R);
    f_status = F_LAYER;
  } else if (state->count == 2) {
    layer_off(_SYMB_R);
    register_code(KC_F);
    unregister_code(KC_F);
    register_code(KC_F);
    f_status = F_HOLD;
  } else {
    unregister_code(KC_F);
    register_code(KC_F);
  }
}

void f_finished(qk_tap_dance_state_t *state, void *user_data) {
  dprintf("f_finished, count: %d, pressed: %d\n", state->count, state->pressed);

  if (f_status == F_LAYER && !state->pressed) {
    register_code(KC_F);
    unregister_code(KC_F);
  }
}

void f_reset(qk_tap_dance_state_t *state, void *user_data) {
  dprintf("f_reset, count: %d, pressed: %d\n", state->count, state->pressed);

  switch (f_status) {
    case F_LAYER:
      layer_off(_SYMB_R);
      break;
    case F_HOLD:
      unregister_code(KC_F);
      break;
  }

  f_status = F_NONE;
}
