#pragma once
#include "./globals.hpp"

namespace Util {
struct Easing {
    float in;
    float out;
    bool reverse;

    Easing(float in, float out, bool reverse) {
        this->in = in;
        this->out = out;
        this->reverse = reverse;
    }

    Easing(float in, float out) {
        this->in = in;
        this->out = out;
        this->reverse = false;
    }

    Easing(float in) {
        this->in = in;
        this->out = 0;
        this->reverse = false;
    }

    Easing() {
        this->in = 1;
        this->out = 0;
        this->reverse = false;
    }
};

CHSV faded_color(CHSV color, float percent) {
    return CHSV(color.h, color.s, color.v * percent);
}

float opacity = 1;
float crop_left = -1000000;
float crop_right = 1000000;
CHSV modify(CHSV color) {
    return faded_color(color, opacity);
}

int wrap_around(int value) {
    while (value < 0) value += RENDER_LED_COUNT;
    while (value >= RENDER_LED_COUNT) value -= RENDER_LED_COUNT;
    return value;
}

void set(int loc, CHSV color) {
    if (float(loc) / RENDER_LED_COUNT < crop_left || float(loc) / RENDER_LED_COUNT > crop_right) return;
    leds[wrap_around(loc) + RENDER_LED_OFFSET] = modify(color);
}

void crop(float left, float right) {
    crop_left = left;
    crop_right = right;
}

void clear_crop() {
    crop_left = -1000000;
    crop_right = 1000000;
}

void clear() {
    clear_crop();
    opacity = 1;
    for (int i = 0; i < LED_COUNT; i++) {
        leds[i] = CRGB(0, 0, 0);
    }
}

void set_line(CHSV color, float start, float end) {
    float realStart = start * RENDER_LED_COUNT;
    float realEnd = end * RENDER_LED_COUNT;
    set(int(floor(realStart)), faded_color(color, ceil(realStart) - realStart));
    set(int(ceil(realEnd)), faded_color(color, realEnd - floor(realEnd)));
    for (int i = ceil(realStart); i < floor(realEnd) + 1; i++) {
        set(i, color);
    }
}

float percent_done_of(float start_s, float end_s, Easing easing) {
    int start_ms = start_s * 1000 - GLOBAL_OFFSET;
    int end_ms = end_s * 1000 - GLOBAL_OFFSET;

    float percent = min(1, max(0, (float(millis()) - start_ms) / float(end_ms - start_ms)));

    if (easing.reverse) percent = 1 - percent;

    if (easing.in == 0) {
        return 1 - pow(1 - percent, easing.out);
    } else if (easing.out == 0) {
        return pow(percent, easing.in);
    } else {
        percent *= 2;
        return (percent <= 1 ? pow(percent, easing.in) : 2 - pow(2 - percent, easing.out)) / 2;
    }
}

bool during(float start_s, float end_s) {
    int current = ((long long)(millis()) - 1000 * 7);
    return current > start_s * 1000 && current < end_s * 1000;
}
}  // namespace Util