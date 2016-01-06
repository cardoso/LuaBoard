#ifndef LUABOARD_HPP
#define LUABOARD_HPP

#include <SFML/Graphics.hpp>
#include <lua.hpp>

class LuaBoard
{
//LuaBoard
public:
  LuaBoard();
  ~LuaBoard();

  int Setup();
  int Loop();

  int UpdateWindowSize();

  int SetupLua();

  int MakeGrid();
  int DrawGrid();

  int MakeCells();
  int DrawCells();

public:
  bool isOpen;

  sf::Color backgroundColor;
  sf::Color gridColor;

  int cellSize;
  int width;
  int height;

  bool isGrid;

  sf::VertexArray grid;
  std::vector<sf::Color> cells;

private:
  sf::Clock deltaTimeClock;


// SFML
public:
  sf::RenderWindow renderWindow;

//Lua
private:
  int luaregister_Color();
  int lua_Color(lua_State* luaState);


private:
  lua_State* luaState;
};

#endif
