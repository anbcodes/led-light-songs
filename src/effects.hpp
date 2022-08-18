#pragma once

#include <FastLED.h>

#include "./globals.hpp"
#include "./util.hpp"

using namespace Util;

namespace Effects {
void bouncing_line(int offset, CHSV color, float speed, int center, int size, int rangeSize) {
    int t = millis() - offset * 1000 + GLOBAL_OFFSET;

    float p = sin(t * speed) * (rangeSize / 2) + center;

    line(color, p - size, p + size);
}

void wipe(int offset, CHSV color, float speed, int direction, int start = 0, int end = LED_COUNT) {
    int t = millis() * direction - offset * 1000 + GLOBAL_OFFSET;

    float percent = min(1, t * speed);

    float amount = pow(percent, 3);
    line(color, start, start + (end - start) * amount);
}

void beat(int offset, CHSV color, float speed_bpm, int center, int minsize, int maxsize) {
    int t = millis() - offset * 1000 + GLOBAL_OFFSET;

    float percent = abs(sin(PI * t * ((0.001 / 60) * speed_bpm)));

    float size = minsize + (maxsize - minsize) * percent;
    line(color, center - size, center + size);
}

void fade_sparkel(float offset, CHSV color, int inv_speed = 100, int count = 10) {
    int t = millis() + offset * 1000 + GLOBAL_OFFSET;

    // for (int i = 0; i < LED_COUNT; i++) {
    //     leds[i] = CRGB(0, 0, 0);
    // }

    for (int i = 0; i < count; i++) {
        int t_offset = i * 25301 + t + (i * (inv_speed / count));
        int amount = sin((float(t_offset % inv_speed) / inv_speed) * PI) * color.v;

        leds[int(floor(t_offset / inv_speed)) * 10313 % 300] = CHSV(color.h, color.s, amount);
    }
}

void from_center(int offset, CHSV color, int size, float speed = 0.01) {
    int t = millis() - offset * 1000 + GLOBAL_OFFSET;
    int center = LED_COUNT / 2;
    float dist = t * speed;
    float s1 = center - size - dist;
    float e1 = center - dist;

    if (s1 < 0) return;

    line(color, s1, e1);

    float s2 = center + dist;
    float e2 = center + size + dist;
    if (e2 > LED_COUNT) return;

    line(color, s2, e2);
}

void fade_out(float start, float end, float power = 1) {
    int start_ms = start * 1000 - GLOBAL_OFFSET;
    int end_ms = end * 1000 - GLOBAL_OFFSET;

    float faded_out = 1 - pow(min(1, max(0, (millis() - start_ms) / (end_ms - start_ms))), power); 

    Util::opacity = faded_out;
}

void fade_in(float start, float end, float power = 1) {
    int start_ms = start * 1000 - GLOBAL_OFFSET;
    int end_ms = end * 1000 - GLOBAL_OFFSET;

    float faded_in = pow(min(1, max(0, (millis() - start_ms) / (end_ms - start_ms))), power); 

    Util::opacity = faded_in;
}

}  // namespace Effects
