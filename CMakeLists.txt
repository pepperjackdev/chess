cmake_minimum_required(VERSION 3.31)

project(chess LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(RAYLIB REQUIRED IMPORTED_TARGET raylib)

file(GLOB_RECURSE CHESS_SOURCES CONFIGURE_DEPENDS
    "src/chess/*.c"
)

file(GLOB_RECURSE UI_SOURCES CONFIGURE_DEPENDS
    "src/ui/*.c"
)


add_library(chess_engine STATIC
    ${CHESS_SOURCES}
)

target_include_directories(chess_engine
    PUBLIC
        include
)

target_compile_options(chess_engine PRIVATE
    $<$<CONFIG:Debug>:-fsanitize=address;-g>
)

target_link_options(chess_engine PRIVATE
    $<$<CONFIG:Debug>:-fsanitize=address>
)


add_executable(gui
    src/apps/gui.c
    ${UI_SOURCES}
)

target_link_libraries(gui PRIVATE
    chess_engine
    PkgConfig::RAYLIB
)

target_compile_options(gui PRIVATE
    $<$<CONFIG:Debug>:-fsanitize=address;-g>
)

target_link_options(gui PRIVATE
    $<$<CONFIG:Debug>:-fsanitize=address>
)


add_executable(perft
    src/apps/perft.c
)

target_link_libraries(perft PRIVATE
    chess_engine
)

target_compile_options(perft PRIVATE
    $<$<CONFIG:Debug>:-fsanitize=address;-g>
)

target_link_options(perft PRIVATE
    $<$<CONFIG:Debug>:-fsanitize=address>
)