#include "daily_planner.h"

#include <iostream>

namespace solution {

int DailyPlanner::exec() {
  while (true) {
    std::string user_input;
    std::cout << "Enter \"add\" / \"see\" / \"exit\": ";
    std::getline(std::cin, user_input);
    if (user_input == "add") {
      user_add();
      separate_output();
    } else if (user_input == "see") {
      user_see();
    } else if (user_input == "exit") {
      break;
    }
  }

  return 0;
}

void DailyPlanner::user_add() {
  std::string user_input;
  while (true) {
    std::cout << "Enter \"event\" or \"birthday\": ";
    std::getline(std::cin, user_input);
    if (user_input == "event") {
      events.insert(Event::ReadFromInput());
      break;
    } else if (user_input == "birthday") {
      Birthday record = Birthday::ReadFromInput();
      auto insertion_result = birthdays.insert(record);
      if (insertion_result.second) {
        birthdayByName.insert(
            make_pair(record.full_name, insertion_result.first));
        birthdayByDate.insert(make_pair(record.date, insertion_result.first));
      } else {
        std::cout << "Error: this record already exist.\n";
      }
      break;
    }
  }
}

void DailyPlanner::user_see() {
  std::string user_input;
  while (true) {
    std::cout << "Enter \"event\" / \"birthday\" \"back\": ";
    std::getline(std::cin, user_input);
    if (user_input == "event") {
      see_event();
      break;
    } else if (user_input == "birthday") {
      see_birthday();
      break;
    } else if (user_input == "back") {
      break;
    }
  }
}

void DailyPlanner::see_event() {
  separate_output('+');
  if (!events.empty()) {
    std::cout << "Events:\n";
    for (auto& event : events) {
      std::cout << event;
      separate_output();
    }
  } else {
    std::cout << "Event's list is empty\n";
    separate_output();
  }
}

void DailyPlanner::see_birthday() {
  if (!birthdays.empty()) {
    std::string user_input;
    while (true) {
      std::cout << "Enter \"all\" / \"by date\" / \"by name\": ";
      std::getline(std::cin, user_input);
      if (user_input == "all") {
        separate_output('+');
        std::cout << "Birthdays:\n";
        for (auto& day : birthdays) {
          std::cout << day;
          separate_output();
        }
        break;
      } else if (user_input == "by date") {
        Date date = Date::ReadFromInput();
        separate_output('+');
        auto record_count = birthdayByDate.count(date);
        if (record_count > 0) {
          auto it = birthdayByDate.find(date);
          for (size_t i = 0; i < record_count; ++i, ++it) {
            std::cout << *(it->second);
            separate_output();
          }
        } else {
          std::cout << "Error: birthdate not found.\n";
        }
        separate_output();
        break;
      } else if (user_input == "by name") {
        FullName full_name = FullName::ReadFromInput();
        separate_output('+');
        auto record_count = birthdayByName.count(full_name);
        if (record_count > 0) {
          auto it = birthdayByName.find(full_name);
          for (size_t i = 0; i < record_count; ++i, ++it) {
            std::cout << *(it->second);
            separate_output();
          }
        } else {
          std::cout << "Error: birthday not found.\n";
        }
        separate_output();
        break;
      }
    }
  } else {
    std::cout << "Birthday's list is empty\n";
    separate_output();
  }
}

void DailyPlanner::separate_output(char symbol) {
  for (size_t i = 0; i < 40; ++i) {
    std::cout << symbol;
  }

  std::cout << '\n';
}

}  // namespace solution
