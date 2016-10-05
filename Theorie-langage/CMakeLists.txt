cmake_minimum_required(VERSION 3.6)
project(Theorie_langage)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

set(SOURCE_FILES main.c Fa.h states_list.h transitions_list.h state.h fa.c states_list.c state_node.h state_node.c list_node.h)
add_executable(Theorie_langage ${SOURCE_FILES})