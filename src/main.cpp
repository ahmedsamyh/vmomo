#define MOMO_COMMON_IMPLEMENTATION
#include <MomoCommon.hpp>

#include <VM.hpp>

// TODO: Add XCHG OpCode (exchange two register's values)
void dummyLoadProgram(VM *vm) {
#define X(op) vm->program[vm->programSize++] = word((op));

  X(MOV);
  X(0);
  X(RAX);

  X(MOV);
  X(1);
  X(RBX);

  X(PRINT); // Jump here
  X(RAX);

  X(ADD); // rax = rax+rbx
  X(RAX);
  X(RBX);

  // exchange rax and rbx
  X(MOVR);
  X(RAX);
  X(RCX); // rcx(temp) = rax;

  X(MOVR);
  X(RBX);
  X(RAX); // rax = rbx;

  X(MOVR);
  X(RCX);
  X(RBX); // rbx = rcx(temp)

  X(JMP);
  X(6);

  X(PEND);
};

int main(int argc, const char **argv) {
  VM vm;
  vm.init();
  dummyLoadProgram(&vm);
  vm.run();
  return 0;
}
