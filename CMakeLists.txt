cmake_minimum_required(VERSION 3.1)
project(Sapling)

set(CMAKE_CXX_STANDARD 11)

add_library(Token "")
add_library(Scanner "")
add_library(AST "")
add_library(Parser "")

include(token/CMakeLists.txt)
include(scanner/CMakeLists.txt)
include(ast/CMakeLists.txt)
include(parser/CMakeLists.txt)
include(tests/CMakeLists.txt)


add_executable(Sapling main.cpp)
target_link_libraries(Sapling Token Scanner AST Parser)