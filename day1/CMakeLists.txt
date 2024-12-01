cmake_minimum_required(VERSION 3.30)
project(problem1)

set(CMAKE_CXX_STANDARD 20)

add_library(common
        common.cpp)
target_sources(common
    PUBLIC
        FILE_SET common_modules TYPE CXX_MODULES
        FILES common.ixx)

add_executable(problem1 problem1.cpp)

target_link_libraries(problem1 PUBLIC common)
