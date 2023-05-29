#include "event.h"

namespace solution {

Event::Event(Date&& expires_, std::string&& description_)
    : expires(expires_), description(description_) {}

}  // namespace solution
