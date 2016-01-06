#include <iostream>

#include "LuaBoard.hpp"

int main(int argc, char** argv)
{
  LuaBoard luaBoard;

  while(luaBoard.isOpen)
  {
    luaBoard.Loop();
  }

  return 0;
}
