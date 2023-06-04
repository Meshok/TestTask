#ifndef DAILY_PLANNER_H
#define DAILY_PLANNER_H

#include <map>
#include <mutex>
#include <set>
#include <thread>

#include "birthday.h"
#include "event.h"

namespace solution {
class DailyPlanner {
 public:
  DailyPlanner();
  int exec();

 private:
  void user_add();
  void user_see();

  void see_event();
  void see_birthday();

  void process_new_day();
  void process_events();
  void process_birthdays();

  bool check_file(const std::string& path, std::string& buffer);
  void save();
  void load();

  void greetings();
  void separate_output(char symbol = '-');

  inline static const std::string app_name = "DailyPlannerV1.0";

  std::set<Event> events;
  std::set<Birthday> birthdays;
  std::mutex event_mutex;
  std::mutex birthday_mutex;

  std::multimap<FullName, std::set<Birthday>::iterator> birthdayByName;
  std::multimap<Date, std::set<Birthday>::iterator> birthdayByDate;
  std::multimap<Date, std::set<Event>::iterator> eventByExpirationDate;
  std::multimap<Date, std::set<Event>::iterator> eventByCreationDate;

  std::set<Birthday>::iterator nextBirthday;
};
}  // namespace solution

#endif  // DAILY_PLANNER_H
