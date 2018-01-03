cmake_minimum_required(VERSION 3.8)
project(streams)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp suspension.cpp stream.cpp fibonacci.cpp)
add_executable(streams ${SOURCE_FILES})