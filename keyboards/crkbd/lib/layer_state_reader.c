
#include QMK_KEYBOARD_H
#include <stdio.h>
#include "crkbd.h"

// in the future, should use (1U<<_LAYER_NAME) instead, but needs to be moved to keymap,c
#define L_QWERTY 0
#define L_SYMB_L 2
#define L_SYMB_R 4
#define L_NAV 8
#define L_NUM 16

char layer_state_str[24];

const char *read_layer_state(void) {
  switch (layer_state)
  {
  case L_QWERTY:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Default");
    break;
  case L_SYMB_L:
  case L_SYMB_R:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Symbol");
    break;
  case L_NAV:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Navigate");
    break;
  case L_NUM:
    snprintf(layer_state_str, sizeof(layer_state_str),"Layer: Numbers");
    break;
  default:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%ld", layer_state);
  }

  return layer_state_str;
}
