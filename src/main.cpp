#define MOMO_COMMON_IMPLEMENTATION
#include <MomoCommon.hpp>

#include <VM.hpp>

void dummyLoadProgram(VM *vm) {
#define X(op) vm->program[vm->programSize++] = word((op));
  X(MOV);
  X(1);
  X(RAX); // <--- rax = 1

  X(MOV);
  X(2);
  X(RBX); // <--- rbx = 2

  X(ADD); // <--- rax = 3

  X(PRINT);
  X(RAX);

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
