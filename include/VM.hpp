#pragma once
#include <MomoCommon.hpp>
#include <common.hpp>
#include <vector>

#define REG(id) registers[id]
#define PROG_CAP 1024
#define MEM_CAP 1024

struct VM {
  // running state of machine
  bool running = true;

  // array of registers
  std::vector<word> registers;
  // array of words that hold the program
  std::vector<word> program;
  size_t programSize = 0;
  // array of words that hold the memory
  std::vector<word> memory;
  size_t memorySize = 0;

  /// MAIN
  void init();
  void run();
  void decodeAndExecute();

  /// UTILITY
  // eats the word at rip and increments rip
  word get();
  void checkValid(word id);
};
