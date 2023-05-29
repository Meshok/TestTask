#include "date.h"

#include <array>

namespace solution {

bool Date::operator<(const Date& other) {
  std::array<int32_t, 3> this_date = {year, month, day};
  std::array<int32_t, 3> other_date = {other.year, other.month, other.day};

  return this_date < other_date;
}

bool Date::operator==(const Date& other) {
  std::array<int32_t, 3> this_date = {year, month, day};
  std::array<int32_t, 3> other_date = {other.year, other.month, other.day};

  return this_date == other_date;
}

}  // namespace solution
