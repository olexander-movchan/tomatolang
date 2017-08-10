cmake_minimum_required(VERSION 3.5)
project(interpreter)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        main.cpp
        lexer.cpp
        lexer.hpp
        syntax_tree.cpp
        syntax_tree.hpp
        parser.cpp
        parser.hpp
        interpreter.cpp
        interpreter.hpp
        types/object.cpp
        types/object.hpp
        types/integer.cpp
        types/integer.hpp
        types/float.cpp
        types/float.hpp
        types/bool.cpp
        types/bool.hpp
        )

add_executable(interpreter ${SOURCE_FILES})
