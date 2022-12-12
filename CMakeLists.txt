set(CMAKE_CXX_COMPILER clang++)

cmake_minimum_required(VERSION 3.24.0)

project(aoc-2022
        LANGUAGES CXX)

message("WARNING: This project only works with LLVM/Clang >= 15.0. This is intentional!")
add_compile_options(-O3 -DNDEBUG)
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

set(SRC "./src")

include_directories(${SRC}/util)

add_executable(one ${SRC}/day01/day01.cxx)
set_target_properties(one 
                        PROPERTIES
                            CXX_STANDARD 20
                            CXX_STANDARD_REQUIRED On)

add_executable(two ${SRC}/day02/day02.cxx)
set_target_properties(two
                        PROPERTIES
                            CXX_STANDARD 20
                            CXX_STANDARD_REQUIRED On)
add_executable(three ${SRC}/day03/day03.cxx)
set_target_properties(three
                        PROPERTIES
                            CXX_STANDARD 20
                            CXX_STANDARD_REQUIRED On)
add_executable(four ${SRC}/day04/day04.cxx)
set_target_properties(four
                        PROPERTIES
                            CXX_STANDARD 20
                            CXX_STANDARD_REQUIRED On)
add_executable(five ${SRC}/day05/day05.cxx)
set_target_properties(five
                        PROPERTIES
                            CXX_STANDARD 20
                            CXX_STANDARD_REQUIRED On)
add_executable(six ${SRC}/day06/day06.cxx)
set_target_properties(six
                        PROPERTIES
                            CXX_STANDARD 20
                            CXX_STANDARD_REQUIRED On)

add_compile_definitions(INPUTS_PATH="${CMAKE_SOURCE_DIR}/inputs")