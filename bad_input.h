#ifndef BAD_INPUT_H
#define BAD_INPUT_H

#include <exception>

class BadInputException : public std::exception {
 public:
  const char* what() const noexcept override { return "Wrong input!"; }
};

#endif  // BAD_INPUT_H
