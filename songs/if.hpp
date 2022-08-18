#pragma once
#include "../src/effects.hpp"


int state[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void song_if() {
  for (int i = 0; i < LED_COUNT; i++) leds[i] = CRGB(0, 0, 0);
  if (during(-3, -2)) leds[150] = CRGB(255, 0, 0);
  if (during(-2, -1)) leds[150] = CRGB(255, 255, 0);
  if (during(-1, 0)) leds[150] = CRGB(0, 255, 0);
  if (during(0, 17.5)) bouncing_line(0, CHSV(100, 255, 255), 0.012, 0, 50, 100);
  if (during(6.75, 16)) from_center(6.75, CHSV(150, 255, 255), 20, 0.04);
  if (during(13.5, 16)) from_center(13.5, CHSV(170, 255, 255), 20, 0.04);
  if (during(17, 17.5)) fade_out(17, 15);
  if (during(17, 20.3)) wipe(17, CHSV(60, 255, 255), 0.00039, 1);
  if (during(20.4, 90)) beat(100, CHSV(0, 255, 255), 140, LED_COUNT/2, 3, 60);
  if (during(34, 90)) beat(100, CHSV(20, 255, 255), 140, 70, 3, 10);
  if (during(34, 90)) beat(100, CHSV(20, 255, 255), 140, 230, 3, 10);
}