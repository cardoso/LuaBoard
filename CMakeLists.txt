cmake_minimum_required(VERSION 2.6)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

project(LuaBoard)

add_executable(LuaBoard src/main.cpp src/LuaBoard.cpp src/lua_LuaBoard.cpp)
target_link_libraries(LuaBoard lua)
target_link_libraries(LuaBoard sfml-system)
target_link_libraries(LuaBoard sfml-window)
target_link_libraries(LuaBoard sfml-graphics)

target_compile_features(LuaBoard PRIVATE cxx_range_for)
