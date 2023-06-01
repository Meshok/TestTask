#include "birthday.h"

#include <tuple>

#include "date_time.h"

namespace solution {

Birthday Birthday::ReadFromInput() {
  Birthday birthday;
  birthday.full_name = FullName::ReadFromInput();
  birthday.date = Date::ReadFromInput();
  Date today = DateTime::now();
  birthday.age = today.year - birthday.date.year;
  if (std::tie(today.month, today.day) >
      std::tie(birthday.date.month, birthday.date.day)) {
    birthday.age -= 1;
  }
  return birthday;
}

bool Birthday::operator<(const Birthday& other) const {
  return std::tie(date, full_name) < std::tie(other.date, other.full_name);
}

bool Birthday::operator==(const Birthday& other) const {
  return std::tie(date, full_name) == std::tie(other.date, other.full_name);
}

std::ostream& operator<<(std::ostream& os, const Birthday& birthday) {
  return os << "Date: " << birthday.date << '\n' << birthday.full_name;
}

}  // namespace solution
