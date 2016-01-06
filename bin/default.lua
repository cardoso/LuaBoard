width = 64
height = 64

Setup = function()
  LuaBoard.SetWindowTitle("LuaBoard")
  LuaBoard.SetBackgroundColor(120, 120, 120)
  LuaBoard.SetCellSize(8);
  LuaBoard.SetWidth(width);
  LuaBoard.SetHeight(height);
end

time = 0
c = 0

Loop = function(dt)
  time = time + dt

  if time > 0.01 then
    time = 0
    c = c + 1
  end

  for x = 1, width do
    for y = 1, height do
      LuaBoard.SetCellColor(x, y, (x+c)%256, (y+c)%256, 255)
    end
  end

  print("DT: "..dt.." seconds")
end
