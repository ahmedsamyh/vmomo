#pragma once
#include <format>
#include <fstream>
#include <iostream>
#include <string>

namespace momo {
#define LOC __FILE__ << ":" << __LINE__ << ":0 "
#define UNREACHABLE() std::cerr << LOC << "Unreachable!\n";
#define UNIMPLEMENTED(msg) std::cerr << LOC << msg << " is unimplemented!\n";
#define PRINT_VAR(var) std::cout << #var << " = " << var << "\n"

#define TYPE_AS_CSTR(type) #type

void err(const std::string &msg);

std::string loadFileToStr(const std::string filename);
}; // namespace momo
////////////////////////////////////////////////////////////
#ifdef MOMO_COMMON_IMPLEMENTATION
namespace momo {
void err(const std::string &msg) {
  std::cerr << "ERROR: " << msg << "\n";
  exit(1);
};

std::string loadFileToStr(const std::string filename) {
  std::ifstream f(filename);
  std::string result = "";
  if (f.fail()) {
    momo::err(std::format("Failed to open file: {}", filename));
  };

  if (f.good()) {
    std::string line;
    while (std::getline(f, line)) {
      result += line + "\n";
    };
  };
  return result;
};
}; // namespace momo
#endif
