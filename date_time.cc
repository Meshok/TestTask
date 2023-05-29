#include "date_time.h"

#include <array>

namespace solution {

bool DateTime::operator<(const DateTime& other) {
  std::array<int32_t, 6> this_date = {year,  month,   day,
                                      hours, minutes, seconds};
  std::array<int32_t, 6> other_date = {other.year,    other.month,
                                       other.day,     other.hours,
                                       other.minutes, other.seconds};

  return this_date < other_date;
}

bool DateTime::operator==(const DateTime& other) {
  std::array<int32_t, 6> this_date = {year,  month,   day,
                                      hours, minutes, seconds};
  std::array<int32_t, 6> other_date = {other.year,    other.month,
                                       other.day,     other.hours,
                                       other.minutes, other.seconds};

  return this_date == other_date;
}

}  // namespace solution
