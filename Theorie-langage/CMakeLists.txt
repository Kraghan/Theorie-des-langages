cmake_minimum_required(VERSION 3.6)
project(Theorie_langage)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

set(SOURCE_FILES main.c fa.h fa.c state.h state.c)
add_executable(Theorie_langage ${SOURCE_FILES})