#include <format>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

#define MOMOSTR_IMPLEMENTATION
#include "./momostr.hpp"

#define COMMON_IMPLEMENTATION
#include "./common.hpp"

struct VM {
  typedef int32_t word;
  // registers
  word rax, rbx, rcx, rdx, rsi, rdi, rbp, rsp, rip;
  enum opCode { NOP = 0, MOV, PEND };

  // array of words that hold the program and memory
  std::vector<word> progMem;

  void boot() {
    rip = 0;
    for (size_t i = 0; i < progMem.size(); ++i) {
      rip = i;
      if (progMem[i] != PEND) {
        // execute program
        word op = progMem[i];
        decode(op);
      };
    };
  };

  void decode(word op) {
    switch (op) {
    case NOP:
      break;
    case MOV:
      UNIMPLEMENTED();
      break;
    case PEND:
      UNIMPLEMENTED();
      break;
    default:
      UNREACHABLE();
      break;
    };
  };
};

int main(int argc, const char **argv) {
  VM vm;
  vm.boot();
  return 0;
}
