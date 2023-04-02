#include <VM.hpp>
#include <common.hpp>

void VM::init() {
  registers = new word(REG_COUNT);
  program = new word(PROG_CAP);
  memory = new word(MEM_CAP);
};

VM::~VM() { delete[] registers; };

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
  case PRINT: {
    // syntax: PRINT, reg
    // prints the value of the register
    word reg_id = get();
    checkValid(reg_id);
    std::cout << strFromRegID(reg_id) << " : " << REG(reg_id) << "\n";
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
