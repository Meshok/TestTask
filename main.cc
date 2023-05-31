#include <chrono>
#include <ctime>
#include <iostream>
#include <set>

#include "birthday.h"
#include "event.h"

int main(void) {
  using namespace solution;
  std::set<Event> events;
  std::set<Birthday> birthdays;
  while (true) {
    std::string user_input;
    std::cout << "Enter \"add\" / \"see\" / \"exit\": ";
    std::getline(std::cin, user_input);
    if (user_input == "add") {
      while (true) {
        std::cout << "Enter \"event\" or \"birthday\": ";
        std::getline(std::cin, user_input);
        if (user_input == "event") {
          events.insert(Event::ReadFromInput());
          break;
        } else if (user_input == "birthday") {
          birthdays.insert(Birthday::ReadFromInput());
          break;
        }
      }
      std::cout << "--------------------------------\n";
    } else if (user_input == "see") {
      if (!events.empty()) {
        std::cout << "++++++++++++++++++++++++++++++++\n";
        std::cout << "Events:\n";
        for (auto& event : events) {
          std::cout << event;
          std::cout << "--------------------------------\n";
        }
      }

      if (!birthdays.empty()) {
        std::cout << "++++++++++++++++++++++++++++++++\n";
        std::cout << "Birthdays:\n";
        for (auto& day : birthdays) {
          std::cout << day;
          std::cout << "--------------------------------\n";
        }
      }
    } else if (user_input == "exit") {
      break;
    }
  }

  return 0;
}
