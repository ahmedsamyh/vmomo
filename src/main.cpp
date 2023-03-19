#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#define MOMOSTR_IMPLEMENTATION
#include ".\momostr.hpp"
#define assert(expr)                                                           \
  if (!(expr)) {                                                               \
    std::cerr << __FILE__ << ":" << __LINE__ << ":0 Assertion Failed: " #expr  \
              << "\n";                                                         \
    exit(1);                                                                   \
  }

#define UNREACHABLE()                                                          \
  std::cerr << __FILE__ << ":" << __LINE__ << ":0 Unreachable!\n";             \
  exit(1);

enum class InstType { PUSH, ADD, SUB, PRINT };

struct Inst {
  InstType type;
  int operand;
};

std::vector<Inst> program;
std::stack<int> stack;

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

void loadProgramFromFile(std::string filePath) {
  std::ifstream f(filePath);
  if (f) {
    while (!f.eof()) {
      std::string line;
      std::getline(f, line);
      std::stringstream ss(line);

      std::string word;
      while (ss >> word) {
        word = toLower(word);
        if (word == "+") {
          program.push_back(Inst{InstType::ADD});
        } else if (word == "-") {
          program.push_back(Inst{InstType::SUB});
        } else if (word == "print") {
          program.push_back(Inst{InstType::PRINT});
        } else if (isAlNum(word)) {
          program.push_back(Inst{InstType::PUSH, atoi(word.c_str())});
        };
      }
    };
  }
  f.close();
};

void runProgram() {
  for (size_t ip = 0; ip < program.size(); ++ip) {
    Inst &inst = program[ip];
    switch (program[ip].type) {
    case InstType::PUSH:
      stack.push(inst.operand);
      break;
    case InstType::ADD: {
      int a = stack.top();
      stack.pop();
      int b = stack.top();
      stack.pop();
      stack.push(a + b);
    } break;
    case InstType::SUB: {
      int a = stack.top();
      stack.pop();
      int b = stack.top();
      stack.pop();
      stack.push(b - a);
    } break;
    case InstType::PRINT:
      std::cout << stack.top() << "\n";
      stack.pop();
      break;
    default:
      UNREACHABLE();
      break;
    };
  };
};

void usage() {
  std::cout << "Usage: vmomo <input> \n";
  exit(0);
}

int main(int argc, const char **argv) {
  if (argc == 1) {
    usage();
  };
  std::string program = argv[0];
  std::string input = argv[1];
  loadProgramFromFile(input);
  runProgram();
  return 0;
}
