#include "birthday.h"

#include <tuple>

namespace solution {

bool Birthday::operator<(const Birthday& other) {
  return std::tie(date, full_name) < std::tie(other.date, other.full_name);
}

bool Birthday::operator==(const Birthday& other) {
  return std::tie(date, full_name) == std::tie(other.date, other.full_name);
}

}  // namespace solution
