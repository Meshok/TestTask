#ifndef BIRTHDAY_H
#define BIRTHDAY_H

#include <string>

#include "date.h"
#include "full_name.h"

namespace solution {
struct Birthday {
  bool operator<(const Birthday& other);
  bool operator==(const Birthday& other);

  Date date;
  FullName full_name;
};
}  // namespace solution

#endif  // BIRTHDAY_H
