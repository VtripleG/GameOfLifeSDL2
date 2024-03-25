cmake_minimum_required(VERSION 3.5)

project(GameOfLife LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(GameOfLife src/main.cpp src/GameBoard.h)

install(TARGETS GameOfLife
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
