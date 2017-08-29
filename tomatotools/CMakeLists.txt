cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(tomatolang)


set(CMAKE_CXX_STANDARD 14)


# Find GNU readline library and header files
find_path(READLINE_INCLUDE_DIR NAMES readline/readline.h)
find_library(READLINE_LIBRARY readline)


set(SOURCE_FILES
        syntax/token.cpp
        syntax/token.hpp
        syntax/lexer.cpp
        syntax/lexer.hpp
        syntax/syntax_tree.cpp
        syntax/syntax_tree.hpp
        syntax/parser.cpp
        syntax/parser.hpp
        errors.cpp
        errors.hpp

        interpreter/main.cpp
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
        interpreter/objects/types.hpp
        syntax/codepoint.cpp syntax/codepoint.hpp)


add_executable(tomato ${SOURCE_FILES})
target_include_directories(tomato PUBLIC . ${READLINE_INCLUDE_DIR})
target_link_libraries(tomato ${READLINE_LIBRARY})


install(TARGETS tomato
        RUNTIME DESTINATION bin)
