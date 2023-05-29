#ifndef EVENT_H
#define EVENT_H

#include <string>

#include "date_time.h"

namespace solution {
struct Event {
  Event(Date&& expires_, std::string&& description_);
  DateTime created;
  Date expires;
  std::string description;
};
}  // namespace solution

#endif  // EVENT_H
