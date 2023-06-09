#ifndef DAILY_PLANNER_BIRTHDAY_H
#define DAILY_PLANNER_BIRTHDAY_H

#include <iostream>
#include <string>

#include "date.h"
#include "full_name.h"

namespace solution {
struct Birthday {
  bool operator<(const Birthday& other) const;
  bool operator==(const Birthday& other) const;
  bool operator<=(const Birthday& other) const;

  static Birthday ReadFromInput();

  Date date;
  FullName full_name;
  mutable int age;
};

std::ostream& operator<<(std::ostream& os, const Birthday& birthday);

}  // namespace solution

#endif  // DAILY_PLANNER_BIRTHDAY_H
