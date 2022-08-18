#pragma once
#include "../src/effects.hpp"

/*
Plan for the song - it's a very slow song - maybe sparklying

*/

int sparkel_state = 0;
int center_state = 0;
int center_state2 = 0;
int center_state3 = 0;
int center_state4 = 0;
int center_state5 = 0;
int center_state6 = 0;
int center_state7 = 0;
int fade_out_state = 0;

bool past(float seconds) {
  return ((long long)(millis()) - 1000 * 7) > seconds * 1000;
}

void broken() {
  for (int i = 0; i < LED_COUNT; i++) {
    leds[i] = CRGB(0, 0, 0);
  }

  if (!past(0)) {
    if (past(-3)) {
      leds[LED_COUNT / 2] = CRGB(255, 0, 0);    
    }
    if (past(-2)) {
      leds[LED_COUNT / 2] = CHSV(20, 255, 255);    
    }
    if (past(-1)) {
      leds[LED_COUNT / 2] = CRGB(0, 255, 0);    
    }
  } else {
    fade_sparkel(&sparkel_state, CHSV(20, 255, 200), 152, 10);
  }

  
}