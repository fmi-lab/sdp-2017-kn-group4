cmake_minimum_required(VERSION 3.8)
project(binary_tree)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp binary-tree.cpp)
add_executable(binary_tree ${SOURCE_FILES})