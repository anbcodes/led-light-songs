#pragma once

#include <FastLED.h>

#include "./globals.hpp"
#include "./util.hpp"

#define GET_PERCENT                                          \
    float percent = percent_done_of(start_s, end_s, easing); \
    if (percent == 0 || percent == 1) return

namespace Effects {
using namespace Util;
void bouncing_line(float start_s, float end_s, CHSV color, float speed, float center, float size, float rangeSize) {
    int t = millis() - start_s * 1000 + GLOBAL_OFFSET;
    if (!during(start_s, end_s)) return;

    float p = sin(t * speed) * (rangeSize / 2) + center;

    set_line(color, p - size, p + size);
}

float beat_offset_ms = 0;

void beat(float start_s, float end_s, CHSV color, float speed_bpm, float center, float minsize, float maxsize) {
    int t = millis() - beat_offset_ms;
    if (!during(start_s, end_s)) return;

    float percent = abs(sin(PI * t * ((0.001 / 60) * speed_bpm)));

    float size = minsize + (maxsize - minsize) * percent;
    set_line(color, center - size, center + size);
}

uint64_t xorshift(const uint64_t& n,int i){
  return n^(n>>i);
}
uint64_t hash(const uint64_t& n){
  uint64_t p = 0x5555555555555555ull; // pattern of alternating 0 and 1
  uint64_t c = 17316035218449499591ull;// random uneven integer constant; 
  return c*xorshift(p*xorshift(n,32),32);
}


void fade_sparkel(float start_s, float end_s, CHSV color, float speed = 0.01, int count = 10) {
    int t = millis() + start_s * 1000 + GLOBAL_OFFSET;
    if (!during(start_s, end_s)) return;

    float inv_speed = 1 / speed;

    for (int i = 0; i < count; i++) {
        int t_offset = i * 25301 + t + (i * (inv_speed / count));
        float amount = sin((float(t_offset % int(inv_speed)) / inv_speed) * PI);

        int index = hash(int(floor(t_offset / inv_speed)) * 10313) % LED_COUNT;

        CHSV new_color = faded_color(color, amount);

        set(index, new_color);
    }
}

void line_from_left_to_right(float start_s, float end_s, CHSV color, float start_loc, float end_loc, float size, Easing easing = {}) {
    GET_PERCENT;
    float location = start_loc + (end_loc - start_loc - size) * percent;
    set_line(color, location, location + size);
}

void line_from_right_to_left(float start_s, float end_s, CHSV color, float start_loc, float end_loc, float size, Easing easing = {}) {
    GET_PERCENT;
    float location = end_loc - (end_loc - start_loc - size) * percent;
    set_line(color, location - size, location);
}

void emerging_line_from_left_to_right(float start_s, float end_s, CHSV color, float start_loc, float end_loc, float size, Easing easing = {}) {
    float cropl = crop_left, cropr = crop_right;
    crop(start_loc, end_loc);
    line_from_left_to_right(start_s, end_s, color, start_loc - size, end_loc + size, size, easing);
    crop(cropl, cropr);
}

void emerging_line_from_right_to_left(float start_s, float end_s, CHSV color, float start_loc, float end_loc, float size, Easing easing = {}) {
    float cropl = crop_left, cropr = crop_right;
    crop(start_loc, end_loc);
    line_from_right_to_left(start_s, end_s, color, start_loc - size, end_loc + size, size, easing);
    crop(cropl, cropr);
}

void two_lines_from_center(float start_s, float end_s, CHSV color, float size, Easing easing = {}) {
    emerging_line_from_right_to_left(start_s, end_s, color, 0, 0.5, size, easing);
    emerging_line_from_left_to_right(start_s, end_s, color, 0.5, 1, size, easing);
}

void fill_left_to_right(float start_s, float end_s, CHSV color, float start_loc, float end_loc, Easing easing = {}) {
    GET_PERCENT;
    float size = (end_loc - start_loc) * percent;
    set_line(color, start_loc, start_loc + size);
}

void fill_right_to_left(float start_s, float end_s, CHSV color, float start_loc, float end_loc, Easing easing = {}) {
    GET_PERCENT;
    float size = (end_loc - start_loc) * percent;
    set_line(color, end_loc - size, end_loc);
}

void fill_from_center(float start_s, float end_s, CHSV color, float center_loc, float size, Easing easing = {}) {
    GET_PERCENT;
    float current_size = size * percent;
    set_line(color, center_loc - current_size, center_loc + current_size);
}

void in_out_from_point(float start_s, float end_s, CHSV color, float center_loc, float size, Easing easing = {}) {
    float duration = end_s - start_s;
    fill_from_center(start_s, end_s - (duration / 2), color, center_loc, size, {easing.in, easing.out, false});
    fill_from_center(start_s + (duration / 2), end_s, color, center_loc, size, {easing.in, easing.out, true});
}

void line(float start_s, float end_s, CHSV color, float start_loc, float end_loc, Easing easing = {}) {
    GET_PERCENT;
    set_line(color, start_loc, end_loc);
}

void countdown() {
    line(-3, -2, CHSV(0, 255, 255), 0.4, 0.6);
    line(-2, -1, CHSV(50, 255, 255), 0.4, 0.6);
    line(-1, -0, CHSV(100, 255, 255), 0.4, 0.6);
}

void reset_fade() {
    opacity = 1;
}

void fade_out(float start_s, float end_s, Easing easing = {}) {
    GET_PERCENT;
    opacity = 1 - percent;
}

void fade_in(float start_s, float end_s, Easing easing = {}) {
    GET_PERCENT;
    opacity = percent;
}

}  // namespace Effects
