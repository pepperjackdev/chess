cmake_minimum_required(VERSION 3.31)
project(chess)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)

add_executable(chess
  src/main.c
  src/chess.c
)

find_package(raylib QUIET)
target_link_libraries(chess PRIVATE raylib)
target_include_directories(chess PRIVATE include)
