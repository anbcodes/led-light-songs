#pragma once
#include "../src/effects.hpp"
#include "../src/util.hpp"

void song_if() {
  Util::clear();
  

  Effects::fade_out(16.5, 17, {3});

  Effects::beat_offset_ms = 100;

  Effects::countdown();
  Effects::bouncing_line(0, 17, CHSV(100, 255, 255), 0.012, 0, 0.2, 0.4);
  Effects::two_lines_from_center(6.75, 7.75, CHSV(150, 255, 255), 0.09, {2});
  Effects::two_lines_from_center(13.5, 14.5, CHSV(150, 255, 255), 0.09, {2});
  // fade_out
  Effects::fill_left_to_right(17, 19.8, CHSV(60, 255, 255), 0, 1, {4.0f});
  Effects::fade_out(20, 20.3, {2});
  Effects::line(19.8, 20.3, CHSV(60, 255, 255), 0, 1);
  Effects::reset_fade();

  Effects::fade_out(60, 61, {2});
  Effects::beat(20.3, 61, CHSV(0, 255, 255), 140, 0.5, 0.07, 0.18);
  Effects::reset_fade();
  Effects::fade_out(46, 47.3, {2});
  Effects::beat(33.7, 47.3, CHSV(20, 255, 255), 140, 0.2, 0.03, 0.08);
  Effects::beat(33.7, 47.3, CHSV(20, 255, 255), 140, 0.8, 0.03, 0.08);
  Effects::reset_fade();

  Effects::in_out_from_point(34.5, 34.8, CHSV(40, 255, 255), 0, 0.1, {0, 1.5});
  Effects::in_out_from_point(41, 41.3, CHSV(40, 255, 255), 0, 0.1, {0, 1.5});

  Effects::two_lines_from_center(62, 62.5, CHSV(180, 200, 255), 0.02, {2});
  Effects::two_lines_from_center(63.8, 64.3, CHSV(180, 200, 255), 0.02, {2});
  Effects::two_lines_from_center(65.5, 66, CHSV(180, 200, 255), 0.02, {2});
  Effects::two_lines_from_center(67.2, 67.7, CHSV(180, 200, 255), 0.02, {2});

  Effects::fade_in(68, 69, {2});
  Effects::line(68, 69, CHSV(180, 200, 180), 0.3, 0.7);
  Effects::fill_from_center(69, 60 + 13, CHSV(180, 200, 180), 0.5, 0.2, {0, 2, true});
  Effects::line(60 + 13, 60 + 14, CHSV(180, 200, 180), 0.495, 0.505);
  Effects::fill_from_center(60 + 14, 60 + 14.4, CHSV(180, 200, 180), 0.5, 0.1, {0, 4, false});
  Effects::line(60 + 14.4, 60 + 15, CHSV(180, 200, 180), 0.4, 0.6);

  Effects::beat(60 + 14.7, 60 + 42, CHSV(180, 200, 180), 70, 0.5, 0.07, 0.25);

  Effects::fade_out(60 + 48, 60 + 49.6);
  Effects::bouncing_line(60 + 42, 60 + 49.6, CHSV(100, 255, 180), 0.012, 0, 0.1, 0.2);

}