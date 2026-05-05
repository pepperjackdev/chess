cmake_minimum_required(VERSION 3.31)
project(chess)

include(FetchContent)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib
  GIT_TAG        932558ca7a54a867f04db3fe4e237ebd887fb8cc
)

FetchContent_MakeAvailable(raylib)

add_executable(chess
  src/main.c
  src/chess.c
  src/ui/page.c
  src/ui/game_page.c
  src/io/fen.c
)

find_package(raylib QUIET)
target_link_libraries(chess PRIVATE raylib)
target_include_directories(chess PRIVATE include)
