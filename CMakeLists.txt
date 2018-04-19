cmake_minimum_required(VERSION 3.1)
project(Sapling)

set(CMAKE_CXX_STANDARD 11)

add_library(Token "")
add_library(Scanner "")

include(token/CMakeLists.txt)
include(scanner/CMakeLists.txt)
include(tests/CMakeLists.txt)

add_executable(Sapling main.cpp)
target_link_libraries(Sapling Token Scanner)