cmake_minimum_required(VERSION 3.30)
project(day6)

set(CMAKE_CXX_STANDARD 20)

add_library(common grid.cpp)
target_sources(common
    PUBLIC
        FILE_SET common_modules TYPE CXX_MODULES
        FILES grid.ixx)

add_executable(part1 part1.cpp)
target_link_libraries(part1 PUBLIC common)

add_executable(part2 part2.cpp)
target_link_libraries(part2 PUBLIC common)
