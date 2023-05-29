#include "full_name.h"

#include <tuple>

namespace solution {

bool FullName::operator<(const FullName& other) {
  auto this_full_name = std::tie(surname, name, patronymic);
  auto other_full_name = std::tie(other.surname, other.name, other.patronymic);

  return this_full_name < other_full_name;
}

bool FullName::operator==(const FullName& other) {
  auto this_full_name = std::tie(surname, name, patronymic);
  auto other_full_name = std::tie(other.surname, other.name, other.patronymic);

  return this_full_name == other_full_name;
}

}  // namespace solution
