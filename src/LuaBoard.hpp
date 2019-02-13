#ifndef LUABOARD_HPP
#define LUABOARD_HPP

#include <SFML/Graphics.hpp>
#include <lua/lua.hpp>

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
  int ClearCells();

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


private:
  lua_State* luaState;
};

#endif
