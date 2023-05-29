#include "date.h"

#include <tuple>

namespace solution {

bool Date::operator<(const Date& other) {
  auto this_date = std::tie(year, month, day);
  auto other_date = std::tie(other.year, other.month, other.day);

  return this_date < other_date;
}

bool Date::operator==(const Date& other) {
  auto this_date = std::tie(year, month, day);
  auto other_date = std::tie(other.year, other.month, other.day);

  return this_date == other_date;
}

}  // namespace solution
