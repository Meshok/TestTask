#ifndef DATE_H
#define DATE_H

#include <cstdint>

namespace solution {
struct Date {
  bool operator<(const Date& other);
  bool operator==(const Date& other);

  int32_t year;
  int32_t month;
  int32_t day;
};
}  // namespace solution

#endif  // DATE_H
