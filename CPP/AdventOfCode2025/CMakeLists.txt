cmake_minimum_required(VERSION 4.0)
project(AdventOfCode2025)

set(CMAKE_CXX_STANDARD 26)

add_executable(AdventOfCode2025 main.cpp)

# Executable for Day 1
add_executable(day01 day01/day01.cpp)
