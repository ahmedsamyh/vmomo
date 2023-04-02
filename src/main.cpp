#define MOMO_COMMON_IMPLEMENTATION
#include <MomoCommon.hpp>

#include <VM.hpp>

void dummyLoadProgram(VM *vm) {
#define X(op) vm->program[vm->programSize++] = word((op));
  X(MOV);
  X(34);
  X(RAX);

  X(MOV);
  X(35);
  X(RBX);

  X(ADD);

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
