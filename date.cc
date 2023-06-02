#include "date.h"

#include <array>
#include <tuple>

#include "bad_input.h"

namespace solution {

bool Date::IsValid() const {
  bool result = true;
  if (year < 1 || month < 1 || month > 12 || day < 1) {
    result = false;
  } else {
    bool is_leap = (year % 400 == 0) || (year % 100 != 0 && year % 4 == 0);
    std::array<int32_t, 12> days_in_month = {31, 28 + is_leap, 31, 30, 31, 30,
                                             31, 31,           30, 31, 30, 31};
    if (day > days_in_month[month - 1]) {
      result = false;
    }
  }

  return result;
}

bool Date::operator<(const Date& other) const {
  auto this_date = std::tie(year, month, day);
  auto other_date = std::tie(other.year, other.month, other.day);

  return this_date < other_date;
}

bool Date::operator==(const Date& other) const {
  auto this_date = std::tie(year, month, day);
  auto other_date = std::tie(other.year, other.month, other.day);

  return this_date == other_date;
}

Date Date::ReadFromInput() {
  Date date;
  std::string input;
  try {
    std::cout << "Day: ";
    std::getline(std::cin, input);
    date.day = std::stoi(input);
    std::cout << "Month: ";
    std::getline(std::cin, input);
    date.month = std::stoi(input);
    std::cout << "Year: ";
    std::getline(std::cin, input);
    date.year = std::stoi(input);
  } catch (const std::invalid_argument& e) {
    throw BadInputException();
  }
  if (!date.IsValid()) {
    throw InvalidDateException();
  }

  return date;
}

std::string Date::DateToString() const {
  return std::to_string(day) + '.' + std::to_string(month) + '.' +
         std::to_string(year);
}

std::ostream& operator<<(std::ostream& os, const Date& date) {
  return os << date.DateToString();
}

}  // namespace solution
