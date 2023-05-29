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
}

#endif  // EVENT_H
