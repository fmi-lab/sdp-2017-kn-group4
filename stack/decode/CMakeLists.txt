cmake_minimum_required(VERSION 3.8)
project(decode)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES decode.cpp)
add_executable(decode ${SOURCE_FILES})