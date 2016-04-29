cmake_minimum_required(VERSION 3.5)
project(Random222Moves)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

set(SOURCE_FILES main.cpp PocketCube.cpp PocketCube.h)
add_executable(Random222Moves ${SOURCE_FILES})