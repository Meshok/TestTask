#ifndef DAILY_PLANNER_BAD_INPUT_H
#define DAILY_PLANNER_BAD_INPUT_H

#include <exception>

class BadInputException : public std::exception {
 public:
  const char* what() const noexcept override { return "Wrong input!"; }
};

#endif  // DAILY_PLANNER_BAD_INPUT_H
