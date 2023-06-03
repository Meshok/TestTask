#include "event.h"

#include <iostream>
#include <tuple>

#include "bad_input.h"

namespace solution {

Event Event::ReadFromInput() {
  std::string description_;
  Date expires_;
  std::cout << "Description: ";
  std::getline(std::cin, description_);
  std::cout << "Enter expiration date:\n";
  try {
    expires_ = Date::ReadFromInput();
    Date today = DateTime::now();
    if (expires_ < today || description_.size() == 0) {
      std::cerr
          << "Wrong input: description is empty or event already expired\n";
      throw BadInputException();
    }
  } catch (const InvalidDateException& e) {
    std::cerr << e.what() << '\n';
    throw BadInputException();
  }

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
