#include "full_name.h"

#include <tuple>

namespace solution {

FullName FullName::ReadFromInput() {
  FullName full_name;
  std::cout << "Surname: ";
  std::getline(std::cin, full_name.surname);
  std::cout << "Name: ";
  std::getline(std::cin, full_name.name);
  std::cout << "Patronymic: ";
  std::getline(std::cin, full_name.patronymic);
  return full_name;
}

std::istream& operator>>(std::istream& is, FullName& full_name) {
  return is >> full_name.surname >> full_name.name >> full_name.patronymic;
}

bool FullName::operator<(const FullName& other) const {
  auto this_full_name = std::tie(surname, name, patronymic);
  auto other_full_name = std::tie(other.surname, other.name, other.patronymic);

  return this_full_name < other_full_name;
}

bool FullName::operator==(const FullName& other) const {
  auto this_full_name = std::tie(surname, name, patronymic);
  auto other_full_name = std::tie(other.surname, other.name, other.patronymic);

  return this_full_name == other_full_name;
}

std::ostream& operator<<(std::ostream& os, const FullName& full_name) {
  os << "Surname: " << full_name.surname << '\n';
  os << "Name: " << full_name.name << '\n';
  os << "Patronymic: " << full_name.patronymic << '\n';
  return os;
}

}  // namespace solution
