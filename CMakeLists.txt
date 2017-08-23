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
        interpreter/objects/object.cpp
        interpreter/objects/object.hpp
        interpreter/objects/integer.cpp
        interpreter/objects/integer.hpp
        interpreter/objects/float.cpp
        interpreter/objects/float.hpp
        interpreter/objects/bool.cpp
        interpreter/objects/bool.hpp
        interpreter/objects/types.hpp)

add_executable(interpreter ${SOURCE_FILES})

target_include_directories(interpreter PUBLIC .)
