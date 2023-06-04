#ifndef DAILY_PLANNER_DESERIALIZE_H
#define DAILY_PLANNER_DESERIALIZE_H

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
std::size_t read(std::istream& is, T& value) {
  const auto pos = is.tellg();
  is.read(reinterpret_cast<char*>(&value), sizeof(T));
  return is.tellg() - pos;
}

template <>
std::size_t read(std::istream& is, std::string& value) {
  const auto pos = is.tellg();
  uint32_t len = 0;
  read(is, len);
  if (len > 0) {
    value.resize(len);
    is.read(value.data(), len);
  }
  return is.tellg() - pos;
}

template <>
std::size_t read(std::istream& is, Date& value) {
  auto pos = is.tellg();
  read(is, value.day);
  read(is, value.month);
  read(is, value.year);
  return is.tellg() - pos;
}

template <>
std::size_t read(std::istream& is, DateTime& value) {
  const auto pos = is.tellg();
  read(is, static_cast<Date&>(value));
  read(is, value.hours);
  read(is, value.minutes);
  read(is, value.seconds);
  return is.tellg() - pos;
}

template <>
std::size_t read(std::istream& is, FullName& value) {
  const auto pos = is.tellg();
  read(is, value.surname);
  read(is, value.name);
  read(is, value.patronymic);
  return is.tellg() - pos;
}

template <>
std::size_t read(std::istream& is, Event& value) {
  const auto pos = is.tellg();
  read(is, value.created);
  read(is, value.expires);
  read(is, value.description);
  return is.tellg() - pos;
}

template <>
std::size_t read(std::istream& is, Birthday& value) {
  const auto pos = is.tellg();
  read(is, value.date);
  read(is, value.full_name);
  return is.tellg() - pos;
}

template <class T>
std::size_t read(std::istream& is, std::set<T>& value) {
  const auto pos = is.tellg();
  uint32_t len = 0;
  read(is, len);
  while (len-- > 0) {
    T temp;
    read(is, temp);
    value.insert(temp);
  }
  return is.tellg() - pos;
}

}  // namespace solution

#endif  // DAILY_PLANNER_DESERIALIZE_H