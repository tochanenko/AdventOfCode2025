cmake_minimum_required(VERSION 4.0)
project(AdventOfCode2025)

set(CMAKE_CXX_STANDARD 26)

add_executable(AdventOfCode2025 main.cpp
        utils/utils.cpp
        utils/utils.h)

# Executable for Day 1
add_executable(day01 day01/day01.cpp
        utils/utils.cpp
        utils/utils.h)
add_executable(day02 day02/day02.cpp
        utils/utils.cpp
        utils/utils.h)
