#pragma once
#include <format>
#include <fstream>
#include <iostream>
#include <string>
namespace momo {

#define LOC __FILE__ << ":" << __LINE__ << ":0 "
#define UNREACHABLE() std::cerr << LOC << "Unreachable!\n";
#define UNIMPLEMENTED(msg) std::cerr << LOC << msg << " is unimplemented!\n";

#define TYPE_AS_CSTR(type) #type

void err(const std::string &msg);

std::string loadFileToStr(const std::string filename);

#ifdef COMMON_IMPLEMENTATION
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
#endif

}; // namespace momo
