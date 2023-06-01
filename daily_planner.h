#ifndef DAILY_PLANNER_H
#define DAILY_PLANNER_H

#include <map>
#include <set>

#include "birthday.h"
#include "event.h"

namespace solution {
class DailyPlanner {
 public:
  int exec();

 private:
  void user_add();
  void user_see();

  void see_event();
  void see_birthday();

  void separate_output(char symbol = '-');

  std::set<Event> events;
  std::set<Birthday> birthdays;
  std::multimap<FullName, std::set<Birthday>::iterator> birthdayByName;
  std::multimap<Date, std::set<Birthday>::iterator> birthdayByDate;
  std::multimap<Date, std::set<Event>::iterator> eventByExpirationDate;
  std::multimap<Date, std::set<Event>::iterator> eventByCreationDate;
};
}  // namespace solution

#endif  // DAILY_PLANNER_H
