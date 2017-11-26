cmake_minimum_required(VERSION 3.8)
project(lists)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp map.cpp filter.cpp foldl.cpp zip.cpp)
add_executable(lists ${SOURCE_FILES})