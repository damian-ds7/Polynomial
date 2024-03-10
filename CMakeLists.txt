cmake_minimum_required(VERSION 3.27)
project(polynomial)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(polynomial
        polynomial.cpp
        polynomial.h)
