#include "birthday.h"

#include <tuple>

#include "bad_input.h"
#include "date_time.h"

namespace solution {

Birthday Birthday::ReadFromInput() {
  Birthday birthday;
  Date today = DateTime::now();
  try {
    birthday.full_name = FullName::ReadFromInput();
    birthday.date = Date::ReadFromInput();
    if (today < birthday.date) {
      std::cerr << "This date has not happened yet.\n";
      throw BadInputException();
    }
  } catch (const InvalidFullNameException&) {
    std::cerr << "Surname and name should not be empty!\n";
    throw BadInputException();
  } catch (const InvalidDateException&) {
    std::cerr << "Wrong date!\n";
    throw BadInputException();
  }
  birthday.age = today.year - birthday.date.year;
  if (std::tie(today.month, today.day) <
      std::tie(birthday.date.month, birthday.date.day)) {
    birthday.age -= 1;
  }
  return birthday;
}

bool Birthday::operator<(const Birthday& other) const {
  return std::tie(date.month, date.day, date.year, full_name) <
         std::tie(other.date.month, other.date.day, other.date.year,
                  other.full_name);
}

bool Birthday::operator==(const Birthday& other) const {
  return std::tie(date, full_name) == std::tie(other.date, other.full_name);
}

bool Birthday::operator<=(const Birthday& other) const {
  return !(other < *this);
}

std::ostream& operator<<(std::ostream& os, const Birthday& birthday) {
  return os << "Date: " << birthday.date << "\nAge: " << birthday.age << '\n'
            << birthday.full_name;
}

}  // namespace solution
