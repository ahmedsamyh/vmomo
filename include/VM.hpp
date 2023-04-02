#pragma once
#include <Register.hpp>
#include <common.hpp>
#include <vector>

#define REG(id) registers[id]

struct VM {
  const size_t PROGRAM_MEM_CAP = 1024 * 2;

  // array of registers
  Register *registers = nullptr;

  // every opcode
  enum opCode { NOP = 0, MOV, PRINT, ADD, PEND };

  // running state of machine
  bool running = true;

  // array of words that hold the program and memory
  std::vector<word> progMem;

  /// TEMP
  void dummyLoadProgram();

  /// MAIN
  VM();
  ~VM();
  void init();
  void run();
  void decodeAndExecute();

  /// UTILITY
  // eats the word at rip and increments rip
  word get();
  void setReg(word id, word val);
};
