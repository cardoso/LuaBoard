#ifndef LUA_LUABOARD_HPP
#define LUA_LUABOARD_HPP

#include <lua.hpp>

int lua_SetWindowTitle(lua_State* luaState);

int lua_SetBackgroundColor(lua_State* luaState);
int lua_SetGridColor(lua_State* luaState);

int lua_SetCellSize(lua_State* luaState);
int lua_SetWidth(lua_State* luaState);
int lua_SetHeight(lua_State* luaState);

int lua_SetCellColor(lua_State* luaState);

#endif
