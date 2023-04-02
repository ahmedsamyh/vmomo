#pragma once
#include <MomoCommon.hpp>
#include <common.hpp>

#define REG(id) registers[id]
#define PROG_CAP 1024 * 1
#define MEM_CAP 1024 * 2

struct VM {
  // running state of machine
  bool running = true;

  // array of registers
  word *registers = nullptr;
  // array of words that hold the program
  word *program = nullptr;
  size_t programSize = 0;
  // array of words that hold the memory
  word *memory = nullptr;
  size_t memorySize = 0;

  /// MAIN
  ~VM();
  void init();
  void run();
  void decodeAndExecute();

  /// UTILITY
  // eats the word at rip and increments rip
  word get();
  void checkValid(word id);
};
