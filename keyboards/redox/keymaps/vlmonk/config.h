#pragma once

/* Use I2C or Serial, not both */
#define USE_SERIAL
// #define USE_I2C

/* Select hand configuration */
#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#undef RGBLIGHT_ENABLE
#define RGBLIGHT_ENABLE = yes

#define RGBLIGHT_ANIMATIONS

#undef RGBLED_NUM
#define RGBLED_NUM 14
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define ONESHOT_TAP_TOGGLE 5
#define ONESHOT_TIMEOUT 5000

#define USB_MAX_POWER_CONSUMPTION 100
