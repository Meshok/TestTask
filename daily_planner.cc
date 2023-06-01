#include "daily_planner.h"

#include <chrono>
#include <iostream>

namespace solution {

DailyPlanner::DailyPlanner() {
  nextEvent = events.end();
  nextBirthday = birthdays.end();
  auto t = std::thread(process_new_day, this);
  t.detach();
}

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
      auto record = Event::ReadFromInput();
      auto insertion_result = events.insert(record);
      if (insertion_result.second) {
        eventByExpirationDate.insert(
            make_pair(record.expires, insertion_result.first));
        eventByCreationDate.insert(make_pair(static_cast<Date>(record.created),
                                             insertion_result.first));
      } else {
        std::cout << "Error: this record already exist.\n";
      }
      break;
    } else if (user_input == "birthday") {
      auto record = Birthday::ReadFromInput();
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
    std::cout << "Enter \"event\" / \"birthday\" / \"back\": ";
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
  if (!events.empty()) {
    std::string user_input;
    while (true) {
      std::cout << "Enter \"all\" / \"by date\" / \"by creation\": ";
      std::getline(std::cin, user_input);
      if (user_input == "all") {
        separate_output('+');
        std::cout << "Events:\n";
        for (auto& event : events) {
          std::cout << event;
          separate_output();
        }
        break;
      } else if (user_input == "by date" || user_input == "by creation") {
        bool byExpirationDate = user_input == "by date";
        auto& dateMap =
            byExpirationDate ? eventByExpirationDate : eventByCreationDate;
        std::cout << "Enter " << (byExpirationDate ? "expiration" : "creation")
                  << " date:\n";
        Date date = Date::ReadFromInput();
        separate_output('+');
        auto record_count = dateMap.count(date);
        if (record_count > 0) {
          auto it = dateMap.find(date);
          for (size_t i = 0; i < record_count; ++i, ++it) {
            std::cout << *(it->second);
            separate_output();
          }
        } else {
          std::cout << "Error: event not found.\n";
          separate_output();
        }
        break;
      }
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
          std::cout << "Error: birthday not found.\n";
          separate_output();
        }
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

void DailyPlanner::process_new_day() {
  using namespace std::chrono;
  while (true) {
    DateTime time = DateTime::now();
    if (time.hours == 0 && time.minutes < 1) {
      process_events();
      process_birthdays();
    }
    time = DateTime::now();

    seconds sleep_time =
        seconds(60u * (60 * (24 - time.hours) - time.minutes) - time.seconds);
    std::this_thread::sleep_for(sleep_time);
  }
}

void DailyPlanner::process_events() {
  if (events.empty()) {
    return;
  }

  auto current = nextEvent;
  auto next = current;
  Date today = DateTime::now();
  for (; next != events.end() && next->expires < today; ++next) {
  }

  for (; current != next; ++current) {
    size_t count = eventByCreationDate.count(current->created);
    auto it = eventByCreationDate.find(current->created);
    for (size_t i = 0; i < count && !(*(it->second) == *current); ++i, ++it) {
    }
    eventByCreationDate.erase(it);
    count = eventByExpirationDate.count(current->expires);
    it = eventByExpirationDate.find(current->expires);
    for (size_t i = 0; i < count && !(*(it->second) == *current); ++i, ++it) {
    }
    eventByExpirationDate.erase(it);
    events.erase(current);
  }
  nextEvent = next;
}

void DailyPlanner::process_birthdays() {
  if (birthdays.empty()) {
    return;
  }

  auto next = nextBirthday;
  Date today = DateTime::now();
  auto eq = [&today](const Date& date) -> bool {
    return date.month == today.month && date.day == today.day;
  };
  for (; next != birthdays.end() && eq(next->date); ++next) {
    next->age = today.year - next->date.year;
  }

  if (next == birthdays.end()) {
    next = birthdays.begin();
    for (; next != nextBirthday && eq(next->date); ++next) {
      next->age = today.year - next->date.year;
    }
  }

  nextBirthday = next;
}

}  // namespace solution
