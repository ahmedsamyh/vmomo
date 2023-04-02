#define MOMO_COMMON_IMPLEMENTATION
#include <MomoCommon.hpp>

#include <VM.hpp>

void dummyLoadProgram(VM *vm) {
#define X(op) vm->program[vm->programSize++] = word((op));
  X(MOV);
  X(10);
  X(RAX);

  X(MOV);
  X(5);
  X(RBX);

  X(MULT);

  X(PRINT);
  X(RAX);

  X(MOV);
  X(5);
  X(RBX);

  X(DIV);

  X(PRINT);
  X(RAX);

  X(PEND);
};

int main(int argc, const char **argv) {
  VM vm;
  vm.init();
  dummyLoadProgram(&vm);
  vm.run();
  return 0;
}
