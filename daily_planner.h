#ifndef DAILY_PLANNER_H
#define DAILY_PLANNER_H

#include <set>

#include "birthday.h"
#include "event.h"

namespace solution {
class DailyPlanner {
 private:
  std::set<Birthday> birthdays;
};
}  // namespace solution

#endif  // DAILY_PLANNER_H
