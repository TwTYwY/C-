cmake_minimum_required(VERSION 3.13)
project(LongArithmetic)
set(CMAKE_CXX_STANDART 20)

add_library(longNum_lib
        LongArithmetic.cpp
        LongArithmetic.hpp
)
Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.8.0
)

FetchContent_MakeAvailable(Catch2)

add_executable(tutor_tests test.cpp)
target_link_libraries(tutor_tests PRIVATE longNum_lib Catch2::Catch2WithMain)