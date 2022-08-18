#include <iostream>
#include <math.h>
#include <thread>
#include <chrono>

float max(float a, float b) {
  return a > b ? a : b;
}

float min(float a, float b) {
  return a < b ? a : b;
}

/**
 Linux (POSIX) implementation of _kbhit().
 Morgan McGuire, morgan@cs.brown.edu
 */
#include <stdio.h>
#include <sys/select.h>

#define PI 3.141592683

#include "./mock/Arduino.h"
#include "./songs/if.hpp"

int main() {
  start_millis(-7000);
  std::cout << "\n";
  // for (int i = 0; i < 100; i++) {
  while(true) {
    song_if();
    // std::cout << "\n";
    std::cout << "\x1B[#F";
    std::cout << ((long long)(millis()) - 1000 * 7) << "ms\n";
    for (int x = 0; x < LED_COUNT; x++) {
      std::cout << "\x1B[48;2;" << int(leds[x].r) << ";" << int(leds[x].g) << ";" << int(leds[x].b) << "m ";
    }
    
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(40ms);
  }
}