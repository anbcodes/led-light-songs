#include "./globals.hpp"

namespace Util {
  float opacity = 1;
  CHSV modify(CHSV color) {
    return faded_color(color, opacity);
  }


  CHSV faded_color(CHSV color, float percent) {
    return CHSV(color.h, color.s, color.v * percent);
  }

  int wrap_around(int value) {
    while (value < 0) value += LED_COUNT;
    while (value >= LED_COUNT) value -= LED_COUNT;
    return value;
  }

  void line(CHSV color, float start, float end) {
    float realStart = start * LED_COUNT;
    float realEnd = end * LED_COUNT;
    leds[wrap_around(int(floor(realStart)))] = modify(faded_color(color, ceil(realStart) - realStart));
    leds[wrap_around(int(ceil(realEnd)))] = modify(faded_color(color, realEnd - floor(realEnd)));
    for (int i = ceil(realStart); i < floor(realEnd) + 1; i++) {
      leds[wrap_around(i)] = color;
    }
  }

  void set(CHSV color, float loc) {
    float realIndex = loc * LED_COUNT;
    leds[wrap_around(int(floor(realIndex)))] = modify(color);
  }

  bool during(float start_s, float end_s) {
    int current = ((long long)(millis()) - 1000 * 7);
    return current > start_s * 1000 && current < end_s * 1000;
  }
}