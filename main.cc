#include <chrono>
#include <ctime>
#include <iostream>

int main(void) {
  auto t = std::chrono::high_resolution_clock::now();
  auto tnow = std::chrono::high_resolution_clock::to_time_t(t);
  tm some_var = *std::localtime(&tnow);
  std::cout << some_var.tm_year + 1900 << " years\n";
  std::cout << some_var.tm_mon + 1 << " months\n";
  std::cout << some_var.tm_mday << " days\n";
  std::cout << some_var.tm_hour << " hours\n";
  std::cout << some_var.tm_min << " minutes\n";
  std::cout << some_var.tm_sec << " seconds\n";

  return 0;
}
