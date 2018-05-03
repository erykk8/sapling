cmake_minimum_required(VERSION 3.1)
project(Sapling)

set(CMAKE_CXX_STANDARD 11)

add_library(Grammar "")
add_library(Scanner "")

include(grammar/CMakeLists.txt)
include(scanner/CMakeLists.txt)
include(tests/CMakeLists.txt)

add_executable(Sapling main.cpp)
target_link_libraries(Sapling Grammar Scanner)