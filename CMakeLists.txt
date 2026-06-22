cmake_minimum_required(VERSION 3.31)
project(chess)

include(FetchContent)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

file(GLOB_RECURSE SRC_FILES 
  "src/*.c" 
  "src/**/*.c"
)

add_executable(chess ${SRC_FILES})

target_compile_options(chess PRIVATE -fsanitize=address -g)
target_link_options(chess PRIVATE -fsanitize=address)


target_link_libraries(chess PRIVATE raylib)
target_include_directories(chess PRIVATE include)
