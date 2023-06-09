#pragma once
#include <string>

typedef int word;
enum REG { RAX = 0, RBX, RCX, RDX, RSI, RDI, RBP, RSP, RIP, REG_COUNT };

// every opcode
enum opCode {
  NOP = 0, // NOP do nothing
  MOV,     // MOV src, dst where src is an immediate value and dst is a register
  MOVR,    // MOVR src, dst where both src and dst are registers
  PRINT,   // PRINT reg, prints the value of reg to stdout
  ADD,     // ADD reg1, reg2 sums reg1 and reg2 and puts the answer in rax
  SUB,     // SUB same as ADD but substraction
  MULT,    // MULT same as ADD but multiplication
  DIV,     // DIV same as ADD but divition
  JMP,     // JMP addr, jumps to an absolute address in the program
  XCHG,    // XCHG reg1, reg2 exchanges the value of reg1 and reg2
  PEND,    // PEND ends the execution of the program
};

std::string strFromRegID(word id);
