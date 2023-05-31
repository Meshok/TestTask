#include "event.h"

#include <iostream>
#include <tuple>

namespace solution {

Event Event::ReadFromInput() {
  Date expires_ = Date::ReadFromInput();
  std::string description_;
  std::cout << "Description: ";
  std::getline(std::cin, description_);
  return Event(expires_, description_);
}

bool Event::operator<(const Event& other) const {
  return std::tie(expires, description, created) <
         std::tie(other.expires, other.description, other.created);
}

bool Event::operator==(const Event& other) const {
  return std::tie(expires, description, created) ==
         std::tie(other.expires, other.description, other.created);
}

std::ostream& operator<<(std::ostream& os, const Event& event) {
  return os << "Created: " << event.created.DateToString() << " --- "
            << event.created.TimeToString() << "\nExpires: " << event.expires
            << "\nDescription: " << event.description << '\n';
}

}  // namespace solution
