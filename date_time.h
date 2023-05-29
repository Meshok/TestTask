#ifndef DATE_TIME_H
#define DATE_TIME_H

#include "date.h"

namespace solution {
struct DateTime : public Date {
  bool operator<(const DateTime& other);
  bool operator==(const DateTime& other);

  int32_t hours;
  int32_t minutes;
  int32_t seconds;
};
}  // namespace solution

#endif  // DATE_TIME_H
