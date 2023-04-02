#include <format>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

#define MOMOSTR_IMPLEMENTATION
#include <momostr.hpp>

#define COMMON_IMPLEMENTATION
#include <common.hpp>

int main(int argc, const char **argv) {
  VM vm;
  vm.init();
  vm.dummyLoadProgram();
  vm.run();
  return 0;
}
