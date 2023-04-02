#include <VM.hpp>
#include <common.hpp>

void VM::init() {
  registers.resize(REG_COUNT);

  for (size_t i = 0; i < REG_COUNT; ++i) {
    REG(i) = 0;
  };

  program.resize(PROG_CAP);
  memory.resize(MEM_CAP);
};

void VM::run() {
  while (running && REG(RIP) < programSize) {
    // execute program
    decodeAndExecute();
  };
  std::cout << "VM ran!\n";
};

void VM::decodeAndExecute() {
  word op = get();
  switch (op) {
  case NOP:
#ifdef DEBUG
    std::cout << "NOP\n";
#endif
    break;
  case MOV: {
    // syntax: MOV, src, dst
    // moves the src to dst
    word src = get();
    word dst = get();
    checkValid(dst);
    REG(dst) = src;
#ifdef DEBUG
    std::cout << "MOV, " << src << ", " << strFromRegID(dst) << "\n";
#endif
  } break;
  case ADD: {
    // syntax: ADD
    // Adds the value of rax and rbx and puts the answer in rax
#ifdef DEBUG
    std::cout << "ADD: " << REG(RAX) << " + " << REG(RBX) << "\n";
#endif
    REG(RAX) = REG(RAX) + REG(RBX);
  } break;
  case SUB: {
    // syntax: SUBB
    // Subtracts the value of rbx from rax (rax - rbx) and puts the answer in
    // rax
#ifdef DEBUG
    std::cout << "SUB: " << REG(RAX) << " - " << REG(RBX) << "\n";
#endif
    REG(RAX) = REG(RAX) - REG(RBX);
  } break;
  case PRINT: {
// syntax: PRINT, reg
// prints the value of the register
#ifdef DEBUG
    std::cout << "PRINT: ";
#endif
    word reg_id = get();
    checkValid(reg_id);
    std::cout << strFromRegID(reg_id) << " = " << REG(reg_id) << "\n";
  } break;
  case PEND:
    // syntax: PEND
    // ends the execution of program
#ifdef DEBUG
    std::cout << "PEND\n";
#endif
    running = false;
    break;
  default:
    UNREACHABLE();
    break;
  };
};

word VM::get() { return program[REG(RIP)++]; };

void VM::checkValid(word id) {
  if (id > REG_COUNT) {
    momo::err("Invalid Register!\n");
  }
}
