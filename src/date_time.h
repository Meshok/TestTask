#ifndef DAILY_PLANNER_DATE_TIME_H
#define DAILY_PLANNER_DATE_TIME_H

#include "date.h"

namespace solution {
struct DateTime : public Date {
 public:
  DateTime(int32_t year_ = 1900, int32_t month_ = 1, int32_t day_ = 1,
           int32_t hours_ = 0, int32_t minutes_ = 0, int32_t seconds_ = 0)
      : Date(year_, month_, day_),
        hours(hours_),
        minutes(minutes_),
        seconds(seconds_){};

  DateTime(const DateTime&) = default;
  ~DateTime() = default;

  DateTime& operator=(const DateTime&) = default;
  DateTime& operator=(DateTime&&) = default;

  static DateTime now();

  bool operator<(const DateTime& other) const;
  bool operator==(const DateTime& other) const;

  std::string TimeToString() const;

  int32_t hours;
  int32_t minutes;
  int32_t seconds;
};

std::ostream& operator<<(std::ostream& os, const DateTime& date);

}  // namespace solution

#endif  // DAILY_PLANNER_DATE_TIME_H
