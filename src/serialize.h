#ifndef DAILY_PLANNER_SERIALIZE_H
#define DAILY_PLANNER_SERIALIZE_H

#include <iostream>
#include <set>
#include <string>

#include "birthday.h"
#include "date.h"
#include "date_time.h"
#include "event.h"
#include "full_name.h"

namespace solution {

template <class T>
std::size_t write(std::ostream& os, const T& value) {
  const auto pos = os.tellp();
  os.write(reinterpret_cast<const char*>(&value), sizeof(T));
  return static_cast<std::size_t>(os.tellp() - pos);
}

template <>
std::size_t write(std::ostream& os, const std::string& value) {
  const auto pos = os.tellp();
  const auto len = static_cast<uint32_t>(value.size());
  write(os, len);
  if (len > 0) {
    os.write(value.data(), len);
  }
  return static_cast<std::size_t>(os.tellp() - pos);
}

template <>
std::size_t write(std::ostream& os, const Date& value) {
  const auto pos = os.tellp();
  write(os, value.day);
  write(os, value.month);
  write(os, value.year);
  return static_cast<std::size_t>(os.tellp() - pos);
}

template <>
std::size_t write(std::ostream& os, const DateTime& value) {
  const auto pos = os.tellp();
  write(os, static_cast<const Date&>(value));
  write(os, value.hours);
  write(os, value.minutes);
  write(os, value.seconds);
  return static_cast<std::size_t>(os.tellp() - pos);
}

template <>
std::size_t write(std::ostream& os, const FullName& value) {
  const auto pos = os.tellp();
  write(os, value.surname);
  write(os, value.name);
  write(os, value.patronymic);
  return static_cast<std::size_t>(os.tellp() - pos);
}

template <>
std::size_t write(std::ostream& os, const Event& value) {
  const auto pos = os.tellp();
  write(os, value.created);
  write(os, value.expires);
  write(os, value.description);
  return static_cast<std::size_t>(os.tellp() - pos);
}

template <>
std::size_t write(std::ostream& os, const Birthday& value) {
  const auto pos = os.tellp();
  write(os, value.date);
  write(os, value.full_name);
  return static_cast<std::size_t>(os.tellp() - pos);
}

template <class T>
std::size_t write(std::ostream& os, const std::set<T>& value) {
  const auto pos = os.tellp();
  const auto len = static_cast<uint32_t>(value.size());
  write(os, len);
  if (len > 0) {
    for (const auto& v : value) {
      write(os, v);
    }
  }
  return static_cast<std::size_t>(os.tellp() - pos);
}

}  // namespace solution

#endif  // DAILY_PLANNER_SERIALIZE_H