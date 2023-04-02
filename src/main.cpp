#define MOMO_COMMON_IMPLEMENTATION
#include <MomoCommon.hpp>

#include <VM.hpp>

void dummyLoadProgram(VM *vm) {
#define X(op) vm->program[vm->programSize++] = word((op));
  X(MOV);
  X(1);
  X(vm->REG(RAX));
  X(MOV);
  X(9);
  X(vm->REG(RBX));
  X(PEND);
};

int main(int argc, const char **argv) {
  VM vm;
  vm.init();
  dummyLoadProgram(&vm);
  vm.run();
  return 0;
}
