#ifndef DAILY_PLANNER_DATE_H
#define DAILY_PLANNER_DATE_H

#include <ctime>
#include <iostream>
#include <string>

namespace solution {

struct Date {
 private:
  bool IsValid() const;

 public:
  Date(int32_t year_ = 1900, int32_t month_ = 1, int32_t day_ = 1)
      : year(year_), month(month_), day(day_){};

  Date(const Date&) = default;
  ~Date() = default;
  Date& operator=(const Date&) = default;
  Date& operator=(Date&&) = default;

  bool operator<(const Date& other) const;
  bool operator==(const Date& other) const;

  static Date ReadFromInput();
  std::string DateToString() const;

  int32_t year;
  int32_t month;
  int32_t day;
};

class InvalidDateException : public std::exception {
 public:
  const char* what() const noexcept override { return "Wrong date!"; }
};

std::ostream& operator<<(std::ostream& os, const Date& date);

}  // namespace solution

#endif  // DAILY_PLANNER_DATE_H
