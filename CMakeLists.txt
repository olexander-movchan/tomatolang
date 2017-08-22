cmake_minimum_required(VERSION 3.5)
project(interpreter)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        main.cpp

        parser/lexer.cpp
        parser/lexer.hpp
        parser/syntax_tree.cpp
        parser/syntax_tree.hpp
        parser/parser.cpp
        parser/parser.hpp
        parser/errors.cpp
        parser/errors.hpp
        parser/token.cpp
        parser/token.hpp

        interpreter/interpreter.cpp
        interpreter/interpreter.hpp
        interpreter/object.cpp
        interpreter/object.hpp
        interpreter/integer.cpp
        interpreter/integer.hpp
        interpreter/float.cpp
        interpreter/float.hpp
        interpreter/bool.cpp
        interpreter/bool.hpp
        )

add_executable(interpreter ${SOURCE_FILES})

target_include_directories(interpreter PUBLIC .)
