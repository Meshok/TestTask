#include <iostream>

#include "daily_planner.h"

int main(void) {
  std::ios_base::sync_with_stdio(false);
  solution::DailyPlanner daily_planner;
  return daily_planner.exec();
}
