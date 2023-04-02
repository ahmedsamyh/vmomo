#pragma once
#include <iostream>
#include <string>

std::string toLower(std::string str);
std::string toUpper(std::string str);
bool isAlNum(const std::string &str);
bool startsWith(std::string prefix, std::string &str);
#ifdef MOMOSTR_IMPLEMENTATION //////////////////////////////////////////////////

std::string toLower(std::string str) {
  std::string res;
  for (size_t i = 0; i < str.size(); ++i) {
    res.push_back(tolower(str[i]));
  };
  return res;
};

std::string toUpper(std::string str) {
  std::string res;
  for (size_t i = 0; i < str.size(); ++i) {
    res.push_back(toupper(str[i]));
  };
  return res;
};

bool isAlNum(const std::string &str) {
  for (auto &c : str) {
    if (!isalnum(c))
      return false;
  };
  return true;
};

// O(N)
// TODO: add optional case-sentive
bool startsWith(std::string prefix, std::string &str) {
  if (prefix.size() > str.size()) {
    std::cerr << "ERROR: size of prefix should be smaller than the size of the "
                 "string!\n";
    exit(1);
  }
  for (size_t i = 0; i < prefix.size(); ++i) {
    if (prefix[i] != str[i]) {
      return false;
    };
  };
  return true;
};

#endif
