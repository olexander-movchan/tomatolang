cmake_minimum_required(VERSION 3.5)
project(interpreter)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        main.cpp
        lexer.cpp
        lexer.hpp
        interpreter.cpp
        interpreter.hpp
        parser.cpp
        parser.hpp
        syntax_tree.cpp
        syntax_tree.hpp
        )

add_executable(interpreter ${SOURCE_FILES})
