cmake_minimum_required(VERSION 3.13)
project(LongArithmetic)
set(CMAKE_CXX_STANDART 20)

add_library(longNum_lib
        LongArithmetic.cpp
        LongArithmetic.hpp
)