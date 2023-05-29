#ifndef FULL_NAME_H
#define FULL_NAME_H

#include <string>

namespace solution {
struct FullName {
  bool operator<(const FullName& other);
  bool operator==(const FullName& other);

  std::string surname;
  std::string name;
  std::string patronymic;
};
}  // namespace solution

#endif  // FULL_NAME_H
