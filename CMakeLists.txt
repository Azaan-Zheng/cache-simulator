cmake_minimum_required(VERSION 3.21)
project(cache C)

set(CMAKE_C_STANDARD 99)

add_executable(cache main.c cache.h cache.c utils.h utils.c defines.h group.h group.c block.h block.c strategy.h strategy.c)
