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
    // syntax: ADD reg1, reg2
    // Adds the value of reg1 and reg2 (reg1 + reg2) and puts the answer in rax
    word reg1 = get();
    word reg2 = get();
    checkValid(reg1);
    checkValid(reg2);
#ifdef DEBUG
    std::cout << "ADD: " << REG(reg1) << " + " << REG(reg2) << "\n";
#endif
    REG(RAX) = REG(reg1) + REG(reg2);
  } break;

  case SUB: {
    // syntax: SUB reg1, reg2
    // Subtracts the value of reg2 from reg1 (reg1 - reg2) and puts the answer
    // in rax
    word reg1 = get();
    word reg2 = get();
    checkValid(reg1);
    checkValid(reg2);
#ifdef DEBUG
    std::cout << "SUB: " << REG(reg1) << " - " << REG(reg2) << "\n";
#endif
    REG(RAX) = REG(reg1) - REG(reg2);
  } break;

  case MULT: {
    // syntax: MULT reg1, reg2
    // Multiplies the value of reg1 and reg2 (reg1 * reg2) and puts the answer
    // in rax
    word reg1 = get();
    word reg2 = get();
    checkValid(reg1);
    checkValid(reg2);
#ifdef DEBUG
    std::cout << "MULT: " << REG(reg1) << " * " << REG(reg2) << "\n";
#endif
    REG(RAX) = REG(reg1) * REG(reg2);
  } break;

  case DIV: {
    // syntax: DIV reg1, reg2
    // Divides the value of reg2 from reg1 (reg1 / reg2) and puts the answer in
    // rax
    word reg1 = get();
    word reg2 = get();
    checkValid(reg1);
    checkValid(reg2);
#ifdef DEBUG
    std::cout << "DIV: " << REG(reg1) << " / " << REG(reg2) << "\n";
#endif
    if (REG(reg2) == 0) {
      momo::err("Division by zero!");
    };
    REG(RAX) = REG(reg1) / REG(reg2);
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
