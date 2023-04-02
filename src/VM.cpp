#include <VM.hpp>
#include <common.hpp>

void VM::dummyLoadProgram() {
  int progstart = 0;
#define X(op) progMem[progstart++] = word((op));
  X(MOV);
  X(1);
  X(REG(RAX));
  X(MOV);
  X(9);
  X(REG(RBX));
  X(PEND);

  progMem.push_back(PEND);
};

void VM::init() {
  rax.id = RAX_ID;
  rbx.id = RBX_ID;
  rcx.id = RCX_ID;
  rdx.id = RDX_ID;
  rsi.id = RSI_ID;
  rdi.id = RDI_ID;
  rbp.id = RBP_ID;
  rsp.id = RSP_ID;
  rip.id = RIP_ID;

  progMem.resize(PROGRAM_MEM_CAP);
};

VM::VM() { registers = new Register(REG_COUNT); };

VM::~VM() { delete[] registers; };

void VM::run() {
  while (running && rip.val < progMem.size()) {
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
    Register::checkValid(dst);
    setReg(dst, src);
#ifdef DEBUG
    std::cout << "MOV, " << src << ", " << Register::strFromRegID(dst) << "\n";
#endif
  } break;
  case ADD: {
    // syntax: ADD
    // Adds the value of rax and rbx and puts the answer in rax
#ifdef DEBUG
    std::cout << "ADD: " << rax.val << " + " << rbx.val << "\n";
#endif
    rax.val = rax.val + rbx.val;
  } break;
  case PRINT: {
    // syntax: PRINT, reg
    // prints the value of the register
    word reg_id = get();
    Register::checkValid(reg_id);
    std::cout << Register::strFromRegID(reg_id) << " : " <<
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

word VM::get() { return progMem[rip.val++]; };

void VM::setReg(word id, word val) {
  switch (id) {
  case RAX_ID:
    rax.val = val;
    break;
  case RBX_ID:
    rbx.val = val;
    break;
  case RCX_ID:
    rcx.val = val;
    break;
  case RDX_ID:
    rdx.val = val;
    break;
  case RSI_ID:
    rsi.val = val;
    break;
  case RDI_ID:
    rdi.val = val;
    break;
  case RBP_ID:
    rbp.val = val;
    break;
  case RSP_ID:
    rsp.val = val;
    break;
  case RIP_ID:
    // TODO: maybe error since the instruction pointer is automatically set?
    rip.val = val;
    break;
  default:
    UNREACHABLE();
    break;
  };
}
