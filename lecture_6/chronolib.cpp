#include <chrono>

int main() {
  using namespace std::chrono;

  // Directly use predefined duration types
  hours Duration2(5);              // Duration2 is of type std::chrono::hours
  milliseconds Duration3(100);     // Duration3 is of type std::chrono::milliseconds

  // Alternatively, use generic std::chrono::duration with explicit template arguments
  duration<int, std::ratio<7 * 24 * 60 * 60>> GenericWeeks(2);  // 2 weeks
  duration<int, std::ratio<3600>> GenericHours(5);              // 5 hours
  duration<int, std::milli> GenericMilliseconds(100);           // 100 ms

  return 0;
}
