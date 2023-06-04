#ifndef DAILY_PLANNER_EVENT_H
#define DAILY_PLANNER_EVENT_H

#include <string>

#include "date_time.h"

namespace solution {
struct Event {
 public:
  Event() = default;
  Event(Date& expires_, std::string& description_)
      : created(DateTime::now()),
        expires(expires_),
        description(description_) {}

  bool operator<(const Event& other) const;
  bool operator==(const Event& other) const;

  static Event ReadFromInput();

  DateTime created;
  Date expires;
  std::string description;
};

std::ostream& operator<<(std::ostream& os, const Event& event);

}  // namespace solution

#endif  // DAILY_PLANNER_EVENT_H
