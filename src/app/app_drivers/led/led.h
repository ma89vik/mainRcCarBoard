#pragma once

#include "error_def.h"

typedef enum {
    LED_GREEN = 0,
    LED_ORANGE,
    LED_RED,
    LED_BLUE,
    LED_MAX,
} led_t;

err_def_t led_set(led_t led, int value);
