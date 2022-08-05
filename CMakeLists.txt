cmake_minimum_required(VERSION 3.22)
project(morse_ui C)

set(CMAKE_C_STANDARD 99)

add_executable(morse_ui main.c morse_functions.c morse_functions.h cereal.c cereal.h)

target_link_libraries(morse_ui ncurses)
