# LuaBoard

A game engine for minimalistic cell based games using lua as scripting language
Early stages

## Compiling

### macOS

```
brew install sfml
brew install lua
cmake .
make
```

## API Documentation (early)

[Callbacks]

Setup()

Loop(deltaTime)

KeyPressed(key)

KeyReleased(key)

MouseClicked(key)

MouseReleased(key)


[Functions]

LuaBoard.SetWindowTitle(title)

LuaBoard.SetBackgroundColor(r, g, b)

LuaBoard.SetGridColor(r, g, b)

LuaBoard.SetCellSize(size)

LuaBoard.SetWidth(width)

LuaBoard.SetHeight(height)

LuaBoard.SetCellColor(x, y, r, g, b)

LuaBoard.ClearCells() -- Clears the board

LuaBoard.GetMousePos() -- Returns table {x, y}
