cmake_minimum_required(VERSION 3.8)
project(interpreter)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp lexer.cpp lexer.hpp)
add_executable(interpreter ${SOURCE_FILES})
