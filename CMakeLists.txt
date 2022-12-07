set(CMAKE_CXX_COMPILER clang++)

cmake_minimum_required(VERSION 3.24.0)

project(aoc-2022
        LANGUAGES CXX)

set(SRC "./src")

include_directories(${SRC}/util)

add_executable(one ${SRC}/day01/day01.cxx)
set_target_properties(one 
                        PROPERTIES
                            CXX_STANDARD 20
                            CXX_STANDARD_REQUIRED On)