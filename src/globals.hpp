#pragma once

#include <FastLED.h>

#define LED_COUNT 300
#define RENDER_LED_COUNT 236
#define RENDER_LED_OFFSET 64

#define DATA_PIN 8

#define GLOBAL_OFFSET -7000
#define GLOBAL_SPEED_DIVISOR 1000

CRGB leds[LED_COUNT];
