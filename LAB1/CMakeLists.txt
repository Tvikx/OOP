cmake_minimum_required(VERSION 3.25)
set(CMAKE_CPP_COMPILER ${CPP_COMPILER})
project(CircularBuffer LANGUAGE CXX)
add_executable( CircularBuffer
                main.cpp
                CircularBuffer.cpp
                CircularBuffer.hpp)
set(CMAKE_CXX_STANDARD 17)