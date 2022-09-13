#include "../src/effects.hpp"
#include "../src/util.hpp"

void test() {
    Util::clear();
    // Effects::fade_sparkel(0, 10, CHSV(20, 255, 255), 0.0002, 10);
    Effects::fade_out(5, 5.5, {2});
    Effects::fill_left_to_right(0, 4.8, CHSV(50, 255, 255), 0, 1, {3.0f});
    Effects::line(4.8, 5.5, CHSV(50, 255, 255), 0, 1);
    // Effects::reset_fade();
}