cmake_minimum_required(VERSION 3.12)
project(MyProject)

include(cmake/gtest.cmake)
include(cmake/sdl2.cmake)

add_subdirectory(src/mod1)
add_subdirectory(src/Lua)
add_subdirectory(src/LuaClass)
add_subdirectory(src/ConfigData)
add_subdirectory(src/WinShape)
add_subdirectory(src/main)