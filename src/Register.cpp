#include <Register.hpp>
#include <common.hpp>

void Register::checkValid(word _id) {
  if (_id > REG::REG_COUNT) {
    momo::err("Invalid register!\n");
  };
};

Register::Register() {
  id = -1;
  val = 0;
}

std::string Register::strFromRegID(word id) {
  switch (id) {
  case RAX:
    return "RAX";
  case RBX:
    return "RBX";
  case RCX:
    return "RCX";
  case RDX:
    return "RDX";
  case RSI:
    return "RSI";
  case RDI:
    return "RDI";
  case RBP:
    return "RBP";
  case RSP:
    return "RSP";
  case RIP:
    return "RIP";
  default:
    UNREACHABLE();
    break;
  };
  return "";
};
