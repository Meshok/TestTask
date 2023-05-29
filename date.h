#ifndef DATE_H
#define DATE_H

#include <cstdint>
#include <ctime>

namespace solution {

struct Date {
 public:
  Date(int32_t year_ = 1900, int32_t month_ = 1, int32_t day_ = 1)
      : year(year_), month(month_), day(day_){};

  Date(const Date&) = default;
  ~Date() = default;

  Date& operator=(const Date&) = default;
  Date& operator=(Date&&) = default;

  bool operator<(const Date& other);
  bool operator==(const Date& other);

  int32_t year;
  int32_t month;
  int32_t day;
};
}  // namespace solution

#endif  // DATE_H
