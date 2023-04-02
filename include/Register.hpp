#pragma once
#include <common.hpp>

struct VM;

struct Register {

  const int REG_COUNT = 9;

  static void checkValid(word _id);

  word id;
  word val;
  Register();

  static std::string strFromRegID(word id);
};
