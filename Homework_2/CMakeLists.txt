cmake_minimum_required(VERSION 3.13)
project(ExpressionDerivative)
set(CMAKE_CXX_STANDART 20)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(expressionDerivative_lib
        Expression.cpp
        Expression.hpp
        Main.cpp
        Parser.cpp
        Parser.hpp
        Token.cpp
        Token.hpp
)

add_executable(differentiator
    Main.cpp
)

target_link_libraries(differentiator PRIVATE expressionDerivative_lib)

include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(tests
        tests.cpp
        Parser.cpp
        Token.cpp
        Expression.cpp
)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)