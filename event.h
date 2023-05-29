#ifndef EVENT_H
#define EVENT_H

#include <string>

#include "date_time.h"

namespace solution {
struct Event {
  DateTime created;
  Date expires;
  std::string description;
};
}  // namespace solution

#endif  // EVENT_H
