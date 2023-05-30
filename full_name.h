#ifndef FULL_NAME_H
#define FULL_NAME_H

#include <iostream>
#include <string>

namespace solution {
struct FullName {
  bool operator<(const FullName& other) const;
  bool operator==(const FullName& other) const;

  static FullName ReadFromInput();

  std::string surname = {};
  std::string name = {};
  std::string patronymic = {};
};

std::ostream& operator<<(std::ostream& os, const FullName& full_name);

}  // namespace solution

#endif  // FULL_NAME_H
