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

struct Inst {
  enum class Type { PUSH, ADD, SUB, MULT, DIV, PRINT };
  Type type;
  int operand;
};

std::vector<Inst> program;
std::stack<int> stack;

void loadProgramFromFile(std::string filePath) {
  std::ifstream f(filePath);
  if (f) {
    while (!f.eof()) {
      std::string line;
      std::getline(f, line);
      std::stringstream ss(line);

      std::string word;

      // lex
      while (ss >> word) {
        word = toLower(word);
        if (word == "+") {
          program.push_back(Inst{Inst::Type::ADD});
        } else if (word == "-") {
          program.push_back(Inst{Inst::Type::SUB});
        } else if (word == "*") {
          program.push_back(Inst{Inst::Type::MULT});
        } else if (word == "/") {
          program.push_back(Inst{Inst::Type::DIV});
        } else if (word == "print") {
          program.push_back(Inst{Inst::Type::PRINT});
        } else if (isAlNum(word)) {
          program.push_back(Inst{Inst::Type::PUSH, atoi(word.c_str())});
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
    case Inst::Type::PUSH:
      stack.push(inst.operand);
      break;
    case Inst::Type::ADD: {
      int a = stack.top();
      stack.pop();
      int b = stack.top();
      stack.pop();
      stack.push(a + b);
    } break;
    case Inst::Type::SUB: {
      int a = stack.top();
      stack.pop();
      int b = stack.top();
      stack.pop();
      stack.push(b - a);
    } break;
    case Inst::Type::MULT: {
      int a = stack.top();
      stack.pop();
      int b = stack.top();
      stack.pop();
      stack.push(b * a);
    } break;
    case Inst::Type::DIV: {
      int a = stack.top();
      stack.pop();
      int b = stack.top();
      stack.pop();
      stack.push(b / a);
    } break;
    case Inst::Type::PRINT:
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
