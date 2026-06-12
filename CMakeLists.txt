cmake_minimum_required(VERSION 3.31)
project(chess)

include(FetchContent)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib
  GIT_TAG        dbc56a87da87d973a9c5baa4e7438a9d20121d28
)

FetchContent_MakeAvailable(raylib)

file(GLOB_RECURSE SRC_FILES 
  "src/*.c"
)

add_executable(chess ${SRC_FILES})

target_compile_options(chess PRIVATE
    -fsanitize=address
    -g
)

target_link_options(chess PRIVATE
    -fsanitize=address
)

target_link_libraries(chess PRIVATE raylib)
target_include_directories(chess PRIVATE include)
