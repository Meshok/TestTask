#include "date_time.h"

#include <ctime>
#include <tuple>

namespace solution {

DateTime DateTime::now() {
  auto time = std::time(nullptr);
  std::tm* t_info = std::localtime(&time);
  return DateTime(t_info->tm_year + 1900, t_info->tm_mon + 1, t_info->tm_mday,
                  t_info->tm_hour, t_info->tm_min, t_info->tm_sec);
}

bool DateTime::operator<(const DateTime& other) {
  auto this_date = std::tie(year, month, day, hours, minutes, seconds);
  auto other_date = std::tie(other.year, other.month, other.day, other.hours,
                             other.minutes, other.seconds);

  return this_date < other_date;
}

bool DateTime::operator==(const DateTime& other) {
  auto this_date = std::tie(year, month, day, hours, minutes, seconds);
  auto other_date = std::tie(other.year, other.month, other.day, other.hours,
                             other.minutes, other.seconds);

  return this_date == other_date;
}

}  // namespace solution
