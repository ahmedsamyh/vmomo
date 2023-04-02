#pragma once
#include <string>

typedef int word;
enum REG { RAX = 0, RBX, RCX, RDX, RSI, RDI, RBP, RSP, RIP, REG_COUNT };

// every opcode
enum opCode {
  NOP = 0,
  MOV,
  PRINT,
  ADD,
  SUB,
  MULT,
  DIV,
  JMP,
  PEND,
};

std::string strFromRegID(word id);
