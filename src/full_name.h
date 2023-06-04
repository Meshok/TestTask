#ifndef DAILY_PLANNER_FULL_NAME_H
#define DAILY_PLANNER_FULL_NAME_H

#include <iostream>
#include <string>

namespace solution {
struct FullName {
  bool operator<(const FullName& other) const;
  bool operator==(const FullName& other) const;

  static FullName ReadFromInput();

  std::string surname = {};
  std::string name = {};
  std::string patronymic = {};
};

std::ostream& operator<<(std::ostream& os, const FullName& full_name);

class InvalidFullNameException : public std::exception {
 public:
  const char* what() const noexcept override {
    return "Wrong name or surname!";
  }
};

}  // namespace solution

#endif  // DAILY_PLANNER_FULL_NAME_H
