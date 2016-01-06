#include <iostream>

#include "lua_LuaBoard.hpp"
#include "LuaBoard.hpp"

int lua_SetWindowTitle(lua_State* luaState)
{
  int argc = lua_gettop(luaState);

  if(argc != 1) {
    lua_pushstring(luaState, "LuaBoard.SetWindowTitle(title): Wrong number of arguments");
    lua_error(luaState);
    return 0;
  }
  if(!lua_isstring(luaState, 1)) {
    lua_pushstring(luaState, "LuaBoard.SetWindowTitle(title): Expected string");
    lua_error(luaState);
    return 0;
  }

  const char* title = lua_tostring(luaState, 1);

  lua_getglobal(luaState, "p_LuaBoard");
  LuaBoard* luaBoard = (LuaBoard*)lua_touserdata(luaState, -1);

  luaBoard->renderWindow.setTitle(title);

  return 1;
}

int lua_SetBackgroundColor(lua_State* luaState)
{
  int argc = lua_gettop(luaState);

  if(argc != 3) {
    lua_pushstring(luaState, "LuaBoard.SetBackgroundColor(r, g, b): Wrong number of arguments");
    lua_error(luaState);
    return 0;
  }
  if(!lua_isinteger(luaState, 1) || !lua_isinteger(luaState, 2) || !lua_isinteger(luaState, 3)) {
    lua_pushstring(luaState, "LuaBoard.SetBackgroundColor(r, g, b): Expected numbers");
    lua_error(luaState);
    return 0;
  }

  int r = lua_tointeger(luaState, 1);
  int g = lua_tointeger(luaState, 2);
  int b = lua_tointeger(luaState, 3);

  if(r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0) {
    lua_pushstring(luaState, "LuaBoard.SetBackgroundColor(r, g, b): Expected numbers between 0 and 255");
    lua_error(luaState);
    return 0;
  }

  lua_getglobal(luaState, "p_LuaBoard");
  LuaBoard* luaBoard = (LuaBoard*)lua_touserdata(luaState, -1);

  luaBoard->backgroundColor = sf::Color(r, g, b);

  return 1;
}

int lua_SetGridColor(lua_State* luaState)
{
  int argc = lua_gettop(luaState);

  if(argc != 3) {
    lua_pushstring(luaState, "LuaBoard.SetGridColor(r, g, b): Wrong number of arguments");
    lua_error(luaState);
    return 0;
  }
  if(!lua_isinteger(luaState, 1) || !lua_isinteger(luaState, 2) || !lua_isinteger(luaState, 3)) {
    lua_pushstring(luaState, "LuaBoard.SetGridColor(r, g, b): Expected numbers");
    lua_error(luaState);
    return 0;
  }

  int r = lua_tointeger(luaState, 1);
  int g = lua_tointeger(luaState, 2);
  int b = lua_tointeger(luaState, 3);

  if(r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0) {
    lua_pushstring(luaState, "LuaBoard.SetGridColor(r, g, b): Expected numbers between 0 and 255");
    lua_error(luaState);
    return 0;
  }

  lua_getglobal(luaState, "p_LuaBoard");
  LuaBoard* luaBoard = (LuaBoard*)lua_touserdata(luaState, -1);

  luaBoard->gridColor = sf::Color(r, g, b);


  return 1;
}

int lua_SetCellSize(lua_State* luaState)
{
  int argc = lua_gettop(luaState);

  if(argc != 1) {
    lua_pushstring(luaState, "LuaBoard.SetCellSize(size): Wrong number of arguments");
    lua_error(luaState);
    return 0;
  }
  if(!lua_isinteger(luaState, 1)) {
    lua_pushstring(luaState, "LuaBoard.SetCellSize(size): Expected number");
    lua_error(luaState);
    return 0;
  }

  int size = lua_tointeger(luaState, 1);

  lua_getglobal(luaState, "p_LuaBoard");
  LuaBoard* luaBoard = (LuaBoard*)lua_touserdata(luaState, -1);

  luaBoard->cellSize = size;

  luaBoard->UpdateWindowSize();
  luaBoard->MakeGrid();

  return 1;
}

int lua_SetWidth(lua_State* luaState)
{
  int argc = lua_gettop(luaState);

  if(argc != 1) {
    lua_pushstring(luaState, "LuaBoard.SetWidth(width): Wrong number of arguments");
    lua_error(luaState);
    return 0;
  }
  if(!lua_isinteger(luaState, 1)) {
    lua_pushstring(luaState, "LuaBoard.SetWidth(width): Expected number");
    lua_error(luaState);
    return 0;
  }

  int width = lua_tointeger(luaState, 1);

  lua_getglobal(luaState, "p_LuaBoard");
  LuaBoard* luaBoard = (LuaBoard*)lua_touserdata(luaState, -1);

  luaBoard->width = width;

  luaBoard->UpdateWindowSize();
  luaBoard->MakeGrid();

  return 1;
}

int lua_SetHeight(lua_State* luaState)
{
  int argc = lua_gettop(luaState);

  if(argc != 1) {
    lua_pushstring(luaState, "LuaBoard.SetHeight(height): Wrong number of arguments");
    lua_error(luaState);
    return 0;
  }
  if(!lua_isinteger(luaState, 1)) {
    lua_pushstring(luaState, "LuaBoard.SetHeight(height): Expected number");
    lua_error(luaState);
    return 0;
  }

  int height = lua_tointeger(luaState, 1);

  lua_getglobal(luaState, "p_LuaBoard");
  LuaBoard* luaBoard = (LuaBoard*)lua_touserdata(luaState, -1);

  luaBoard->height = height;

  luaBoard->UpdateWindowSize();
  luaBoard->MakeGrid();

  return 1;
}

int lua_SetCellColor(lua_State* luaState)
{
  int argc = lua_gettop(luaState);

  if(argc != 5) {
    lua_pushstring(luaState, "LuaBoard.SetCellColor(x, y, r, g, b): Wrong number of arguments");
    lua_error(luaState);
    return 0;
  }
  if(!lua_isinteger(luaState, 1) || !lua_isinteger(luaState, 2) || !lua_isinteger(luaState, 3) || !lua_isinteger(luaState, 4) || !lua_isinteger(luaState, 5)) {
    lua_pushstring(luaState, "LuaBoard.SetCellColor(x, y, r, g, b): Expected numbers");
    lua_error(luaState);
    return 0;
  }

  int x = lua_tointeger(luaState, 1) -1;
  int y = lua_tointeger(luaState, 2) -1;
  int r = lua_tointeger(luaState, 3);
  int g = lua_tointeger(luaState, 4);
  int b = lua_tointeger(luaState, 5);

  if(r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0) {
    lua_pushstring(luaState, "LuaBoard.SetCellColor(x, y, r, g, b): Expected numbers between 0 and 255 for colors");
    lua_error(luaState);
    return 0;
  }

  lua_getglobal(luaState, "p_LuaBoard");
  LuaBoard* luaBoard = (LuaBoard*)lua_touserdata(luaState, -1);

  if(x >= luaBoard->width || x < 0 || y >= luaBoard->height || y < 0) {
    lua_pushstring(luaState, "LuaBoard.SetCellColor(x, y, r, g, b): Coordinates out of range");
    lua_error(luaState);
    return 0;
  }


  luaBoard->cells[y*luaBoard->height+x] = sf::Color(r, g, b);

  return 1;
}
