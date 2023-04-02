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
  case MOVR: {
    // syntax: MOVR src, dst
    // same as MOV but with registers
    word src = get();
    word dst = get();
    checkValid(src);
    checkValid(dst);
    REG(dst) = REG(src);
#ifdef DEBUG
    std::cout << "MOVR, " << strFromRegID(src) << ", " << strFromRegID(dst)
              << "\n";
#endif
  } break;
  case ADD: {
    // syntax: ADD
    // Adds the value of rax and rbx (rax + rbx) and puts the answer in rax
#ifdef DEBUG
    std::cout << "ADD: " << REG(RAX) << " + " << REG(RBX) << "\n";
#endif
    REG(RAX) = REG(RAX) + REG(RBX);
  } break;
  case SUB: {
    // syntax: SUB
    // Subtracts the value of rbx from rax (rax - rbx) and puts the answer in
    // rax
#ifdef DEBUG
    std::cout << "SUB: " << REG(RAX) << " - " << REG(RBX) << "\n";
#endif
    REG(RAX) = REG(RAX) - REG(RBX);
  } break;
  case MULT: {
    // syntax: MULT
    // Multiplies the value of rax and rbx (rax * rbx) and puts the answer in
    // rax
#ifdef DEBUG
    std::cout << "MULT: " << REG(RAX) << " * " << REG(RBX) << "\n";
#endif
    REG(RAX) = REG(RAX) * REG(RBX);
  } break;
  case DIV: {
    // syntax: DIV
    // Divides the value of rbx from rax (rax / rbx) and puts the answer in
    // rax
#ifdef DEBUG
    std::cout << "DIV: " << REG(RAX) << " / " << REG(RBX) << "\n";
#endif
    // TODO: Handle divide by zero
    REG(RAX) = REG(RAX) / REG(RBX);
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
  case JMP: {
    // syntax: JMP, addr
    // jumps to the specified address (absolute)
    word addr = get();
    if (addr < 0 || addr >= programSize) {
      momo::err("Jump Address invalid!\n");
    };
    REG(RIP) = addr;
#ifdef DEBUG
    std::cout << "JMP, " << addr << "\n";
#endif

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
