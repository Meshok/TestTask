#include "daily_planner.h"

#include <chrono>
#include <fstream>
#include <iostream>

#include "bad_input.h"
#include "deserialize.h"
#include "serialize.h"

namespace solution {

DailyPlanner::DailyPlanner() { nextBirthday = birthdays.end(); }

int DailyPlanner::exec() {
  auto t = std::thread(&DailyPlanner::process_new_day, this);
  t.detach();

  greetings();

  while (true) {
    std::string user_input;
    std::cout << "Enter \"add\" / \"see\" / \"save\" / \"load\" / \"exit\": ";
    std::getline(std::cin, user_input);
    try {
      if (user_input == "add") {
        user_add();
        separate_output();
      } else if (user_input == "see") {
        user_see();
      } else if (user_input == "save") {
        save();
      } else if (user_input == "load") {
        load();
      } else if (user_input == "exit") {
        break;
      }
    } catch (const std::exception&) {
      std::cout << "You were returned back to main menu.\n";
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

      std::lock_guard<std::mutex> lock_event(event_mutex);
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

      std::lock_guard<std::mutex> lock_birthday(birthday_mutex);
      auto insertion_result = birthdays.insert(record);
      if (insertion_result.second) {
        Date today = DateTime::now();
        auto less_or_eq = [](const Date& l, const Date& r) -> bool {
          return std::tie(l.month, l.day) <= std::tie(r.month, r.day);
        };
        if ((nextBirthday == birthdays.end() &&
             less_or_eq(today, insertion_result.first->date)) ||
            (nextBirthday != birthdays.end() &&
             less_or_eq(today, insertion_result.first->date) &&
             *insertion_result.first < *nextBirthday)) {
          nextBirthday = insertion_result.first;
        }

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
      std::cout
          << "Enter \"all\" / \"today\" / \"by date\" / \"by creation\": ";
      std::getline(std::cin, user_input);
      if (user_input == "all") {
        separate_output('+');
        std::cout << "Events:\n";
        std::lock_guard<std::mutex> lock_event(event_mutex);
        for (auto& event : events) {
          std::cout << event;
          separate_output();
        }
        break;
      } else if (user_input == "today") {
        Date date = DateTime::now();
        separate_output('+');
        std::cout << "Today's events:\n";
        std::lock_guard<std::mutex> lock_event(event_mutex);
        auto record_count = eventByExpirationDate.count(date);
        if (record_count > 0) {
          auto it = eventByExpirationDate.find(date);
          for (size_t i = 0; i < record_count; ++i, ++it) {
            std::cout << *(it->second);
            separate_output();
          }
        } else {
          std::cout << "Today there are no events.\n";
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
        std::lock_guard<std::mutex> lock_event(event_mutex);
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
      std::cout << "Enter \"all\" / \"today\" / \"by date\" / \"by name\": ";
      std::getline(std::cin, user_input);
      if (user_input == "all") {
        separate_output('+');
        std::cout << "Birthdays:\n";

        std::lock_guard<std::mutex> lock_birthday(birthday_mutex);
        for (auto& day : birthdays) {
          std::cout << day;
          separate_output();
        }
        break;
      } else if (user_input == "today") {
        Date date = DateTime::now();
        separate_output('+');
        std::cout << "Today's birthdays:\n";
        std::lock_guard<std::mutex> lock_event(birthday_mutex);
        auto eq = [&date](const Date& other) {
          return date.month = other.month && date.day == other.day;
        };
        if (nextBirthday != birthdays.end() && eq(nextBirthday->date)) {
          for (auto it = nextBirthday; it != birthdays.end(); ++it) {
            std::cout << *it;
            separate_output();
          }
        } else {
          std::cout << "Today there are no birthdays.\n";
          separate_output();
        }
        break;
      } else if (user_input == "by date") {
        Date date = Date::ReadFromInput();
        separate_output('+');

        std::lock_guard<std::mutex> lock_birthday(birthday_mutex);
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

        std::lock_guard<std::mutex> lock_birthday(birthday_mutex);
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

void DailyPlanner::greetings() {
  std::cout << "Hello and welcome to DailyPlanner v1.0!\n";
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
        seconds(5ull + 60ull * (60ull * (24ull - time.hours) - time.minutes) -
                time.seconds);
    std::this_thread::sleep_for(sleep_time);
  }
}

void DailyPlanner::process_events() {
  std::lock_guard<std::mutex> lock_event(event_mutex);

  if (events.empty()) {
    return;
  }

  auto next = events.begin();
  auto end = next;
  Date today = DateTime::now();
  for (; end != events.end() && end->expires < today; ++end) {
  }

  if (end == events.end()) {
    events.clear();
    eventByCreationDate.clear();
    eventByExpirationDate.clear();
  } else {
    eventByExpirationDate.erase(eventByExpirationDate.begin(),
                                eventByExpirationDate.upper_bound(today));
    for (auto current = next++; current != end; current = next++) {
      size_t count = eventByCreationDate.count(current->created);
      auto it = eventByCreationDate.find(current->created);
      for (size_t i = 0; i < count && !(*(it->second) == *current); ++i, ++it) {
      }
      eventByCreationDate.erase(it);
      events.erase(current);
    }
  }
}

void DailyPlanner::process_birthdays() {
  std::lock_guard<std::mutex> lock_birthday(birthday_mutex);

  if (birthdays.empty()) {
    return;
  }

  Date today = DateTime::now();
  auto less_or_eq = [](const Date& l, const Date& r) -> bool {
    return std::tie(l.month, l.day) <= std::tie(r.month, r.day);
  };

  if (nextBirthday == birthdays.end() &&
      less_or_eq(today, birthdays.begin()->date)) {
    nextBirthday = birthdays.begin();
  }

  for (;
       nextBirthday != birthdays.end() && less_or_eq(nextBirthday->date, today);
       ++nextBirthday) {
    nextBirthday->age += 1;
  }
}

void DailyPlanner::save() {
  std::cout << "Enter the file name to save the state: ";
  std::string user_input;
  std::getline(std::cin, user_input);
  auto os = std::ofstream(user_input);
  if (os.is_open()) {
    {
      std::lock_guard<std::mutex> event_lock(event_mutex);
      write(os, events);
    }
    {
      std::lock_guard<std::mutex> birthday_lock(birthday_mutex);
      write(os, birthdays);
    }
  } else {
    std::cerr << "File \"" << user_input << "\" cannot be opened.\n";
    std::cout << "The save has been canceled.\n";
  }
}

void DailyPlanner::load() {
  std::cout << "Enter the file name to load the state (make "
               "sure you have entered the correct file): ";
  std::string user_input;
  std::getline(std::cin, user_input);
  auto is = std::ifstream(user_input);
  if (is.is_open()) {
    Date today = DateTime::now();

    decltype(events) events_;
    decltype(eventByCreationDate) eventByCreationDate_;
    decltype(eventByExpirationDate) eventByExpirationDate_;
    decltype(birthdays) birthdays_;
    decltype(birthdayByDate) birthdayByDate_;
    decltype(birthdayByName) birthdayByName_;
    read(is, events_);
    read(is, birthdays_);

    auto exp = events_.begin();
    while (exp != events_.end() && exp->expires < today) {
      ++exp;
    }
    events_.erase(events_.begin(), exp);
    for (auto it = events_.begin(); it != events_.end(); ++it) {
      eventByCreationDate_.insert(
          make_pair(static_cast<Date>(it->created), it));
      eventByExpirationDate_.insert(make_pair(it->expires, it));
    }

    auto greater = [&today](const Date& d) {
      return std::tie(d.month, d.day) > std::tie(today.month, today.day);
    };
    nextBirthday = birthdays_.end();
    for (auto it = birthdays_.begin(); it != birthdays_.end(); ++it) {
      if (nextBirthday == birthdays_.end() && greater(it->date)) {
        nextBirthday = it;
      }
      int age = today.year - it->date.year;
      if (std::tie(today.month, today.day) <
          std::tie(it->date.month, it->date.day)) {
        age -= 1;
      }
      it->age = age;
      birthdayByDate_.insert(make_pair(it->date, it));
      birthdayByName_.insert(make_pair(it->full_name, it));
    }

    {
      std::lock_guard<std::mutex> event_lock(event_mutex);
      events = std::move(events_);
      eventByCreationDate = std::move(eventByCreationDate_);
      eventByExpirationDate = std::move(eventByExpirationDate_);
    }
    {
      std::lock_guard<std::mutex> birthday_lock(birthday_mutex);
      birthdays = std::move(birthdays_);
      birthdayByDate = std::move(birthdayByDate_);
      birthdayByName = std::move(birthdayByName_);
    }
    std::cout << "The load has been successful.\n";
  } else {
    std::cerr << "File \"" << user_input << "\" cannot be opened.\n";
    std::cout << "The load has been canceled.\n";
  }
}

}  // namespace solution
