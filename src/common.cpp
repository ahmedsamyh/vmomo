#include <common.hpp>

std::string strFromRegID(word id) {
  switch (id) {
  case 0:
    return "rax";
  case 1:
    return "rbx";
  case 2:
    return "rcx";
  case 3:
    return "rdx";
  case 4:
    return "rsi";
  case 5:
    return "rdi";
  case 6:
    return "rbp";
  case 7:
    return "rsp";
  case 8:
    return "rip";
  };
  return "";
};
