#include <chrono>

std::chrono::_V2::system_clock::time_point program_start;

int millis_offset = 5000;

void start_millis(int at_ms = 0) {
  millis_offset = at_ms + 7000;
  program_start = std::chrono::high_resolution_clock::now();
}

unsigned long millis() {
  auto current_time = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(current_time - program_start).count() + millis_offset;
}

