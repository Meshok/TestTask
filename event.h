#ifndef EVENT_H
#define EVENT_H

#include <string>

#include "date_time.h"

namespace solution {
struct Event {
 public:
  Event(Date&& expires_, std::string&& description_)
      : created(DateTime::now()),
        expires(expires_),
        description(description_) {}

  DateTime created;
  Date expires;
  std::string description;
};
}  // namespace solution

#endif  // EVENT_H
