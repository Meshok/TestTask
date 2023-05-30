#include <chrono>
#include <ctime>
#include <iostream>
#include <set>

#include "birthday.h"

int main(void) {
  using namespace solution;
  std::set<Birthday> birthdays;
  for (size_t i = 0; i < 2; ++i) {
    birthdays.insert(Birthday::ReadFromInput());
    std::cout << "-----------------\n";
  }

  for (auto& day : birthdays) {
    std::cout << day;
    std::cout << "-----------------\n";
  }

  return 0;
}
