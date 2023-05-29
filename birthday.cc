#include "birthday.h"

#include <tuple>

namespace solution {

bool Birthday::operator<(const Birthday& other) {
  auto this_birthday = std::make_tuple(date, full_name);
  auto other_birthday = std::make_tuple(other.date, other.full_name);

  return this_birthday < other_birthday;
}

bool Birthday::operator==(const Birthday& other) {
  auto this_birthday = std::make_tuple(date, full_name);
  auto other_birthday = std::make_tuple(other.date, other.full_name);

  return this_birthday == other_birthday;
}

}  // namespace solution
