cmake_minimum_required(VERSION 3.5)

project(GameOfLife LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

add_executable( ${PROJECT_NAME}
  src/main.cpp src/GameBoard.h
  src/GameScene.h src/GameScene.cpp )

install(TARGETS GameOfLife
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

target_link_libraries(
      ${PROJECT_NAME} PRIVATE
      SDL2::SDL2
      SDL2::SDL2main
    )
