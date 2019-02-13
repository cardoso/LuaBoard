#include <iostream>

#include "LuaBoard.hpp"
#include "lua_LuaBoard.hpp"

//LuaBoard
LuaBoard::LuaBoard()
{
  // SFML
  this->renderWindow.create(sf::VideoMode(64*8, 64*8), "LuaBoard");
  this->backgroundColor = sf::Color(255,255,255);
  this->gridColor = sf::Color(0,0,0);
  this->isOpen = renderWindow.isOpen();
  this->cellSize = 8;
  this->width = 64;
  this->height = 64;
  this->isGrid = true;

  this->renderWindow.setVerticalSyncEnabled(true);

  //LuaBoard
  this->MakeGrid();
  this->MakeCells();

  // Lua
  this->SetupLua();
}

LuaBoard::~LuaBoard()
{
  lua_close(this->luaState);
}

int LuaBoard::Loop()
{
  sf::Event event;
  while(this->renderWindow.pollEvent(event))
  {
    if(event.type == sf::Event::Closed)
      this->renderWindow.close();
    if(event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::R))
      this->SetupLua();

    if(event.type == sf::Event::MouseButtonPressed)
    {
      lua_getglobal(this->luaState, "MouseClicked");
      lua_pushnumber(this->luaState, event.mouseButton.button);

      int x = sf::Mouse::getPosition(this->renderWindow).x/this->cellSize + 1;
      int y = sf::Mouse::getPosition(this->renderWindow).y/this->cellSize + 1;

      lua_pushinteger(this->luaState, x);
      lua_pushinteger(this->luaState, y);
      lua_call(this->luaState, 3, 0);
    }

    if(event.type == sf::Event::MouseButtonReleased)
    {
      lua_getglobal(this->luaState, "MouseReleased");

      lua_pushnumber(this->luaState, event.mouseButton.button);

      int x = sf::Mouse::getPosition(this->renderWindow).x/this->cellSize + 1;
      int y = sf::Mouse::getPosition(this->renderWindow).y/this->cellSize + 1;

      lua_pushinteger(this->luaState, x);
      lua_pushinteger(this->luaState, y);
      lua_call(this->luaState, 3, 0);
    }

    if(event.type == sf::Event::KeyPressed)
    {
      lua_getglobal(this->luaState, "KeyPressed");
      lua_pushinteger(this->luaState, event.key.code);

      lua_call(this->luaState, 1, 0);
    }

    if(event.type == sf::Event::KeyReleased)
    {
      lua_getglobal(this->luaState, "KeyReleased");
      lua_pushinteger(this->luaState, event.key.code);

      lua_call(this->luaState, 1, 0);
    }
  }

  this->renderWindow.clear(this->backgroundColor);

  this->DrawCells();
  if(isGrid) this->DrawGrid();

  lua_getglobal(this->luaState, "Loop");
  lua_pushnumber(this->luaState, this->deltaTimeClock.restart().asSeconds());
  lua_call(this->luaState, 1, 0);

  this->renderWindow.display();

  this->isOpen = this->renderWindow.isOpen();

  return 1;
}

int LuaBoard::SetupLua()
{
  this->luaState = luaL_newstate();
  luaopen_base(this->luaState);

  lua_pushlightuserdata(this->luaState, (void*)this);
  lua_setglobal(this->luaState, "p_LuaBoard");

  const luaL_Reg luaBoardFuncs[] =
  {
    {"SetWindowTitle", lua_SetWindowTitle},
    {"SetBackgroundColor", lua_SetBackgroundColor},
    {"SetGridColor", lua_SetGridColor},
    {"SetCellSize", lua_SetCellSize},
    {"SetWidth", lua_SetWidth},
    {"SetHeight", lua_SetHeight},
    {"SetCellColor", lua_SetCellColor},
    {"ClearCells", lua_ClearCells},
    {"GetMousePos", lua_GetMousePos},
    {NULL, NULL}
  };

  luaL_newlib(this->luaState, luaBoardFuncs);
  lua_setglobal(this->luaState, "LuaBoard");

  luaL_dofile(this->luaState, "./default.lua");

  lua_getglobal(this->luaState, "Setup");
  lua_call(this->luaState, 0, 0);

  return 0;
}

int LuaBoard::UpdateWindowSize()
{
  uint width = (uint)this->width*(uint)this->cellSize;
  uint height = (uint)this->height*(uint)this->cellSize;

  sf::Vector2u size = sf::Vector2u(width, height);

  this->renderWindow.setSize(size);

  return 1;
}

int LuaBoard::MakeGrid()
{
  int verticalLines = this->width*2;
  int horizontalLines = this->height*2;

  int totalLines = verticalLines + horizontalLines;

  this->grid = sf::VertexArray(sf::Lines, verticalLines + horizontalLines);

  for(int x = 0; x < verticalLines; x++)
  {
    this->grid[x].position = x%2==0 ?
    sf::Vector2f(x*this->cellSize/2, 0) :
    sf::Vector2f((x-1)*this->cellSize/2, this->cellSize*this->height);

    this->grid[x].color = sf::Color::Black;
  }

  for(int y = 0; y < horizontalLines; y++)
  {
    this->grid[y + verticalLines].position = y%2==0 ?
    sf::Vector2f(0, y*this->cellSize/2) :
    sf::Vector2f(this->cellSize*this->width, (y-1)*this->cellSize/2);

    this->grid[y + verticalLines].color = sf::Color::Black;
  }

  return 1;
}

int LuaBoard::DrawGrid()
{
  this->renderWindow.draw(this->grid);

  return 1;
}

int LuaBoard::MakeCells()
{
  this->cells.clear();

  int size = this->width*this->height;

  for(int i = 0; i < size; i++)
  {
    this->cells.insert(this->cells.end(), this->backgroundColor);
  }

  return 1;
}

int LuaBoard::DrawCells()
{
  sf::RectangleShape cell;
  cell.setSize(sf::Vector2f(this->cellSize, this->cellSize));

  for(int i = 0; i < this->cells.size(); i++)
  {
    if(this->cells[i] == this->backgroundColor)
      continue;

    int x = (i%this->width)*this->cellSize;
    int y = (i/this->width)*this->cellSize;

    cell.setFillColor(this->cells[i]);
    cell.setPosition(x, y);

    this->renderWindow.draw(cell);
  }

  return 1;
}

int LuaBoard::ClearCells()
{
  for(auto& cell : this->cells)
    cell = this->backgroundColor;

  return 1;
}
