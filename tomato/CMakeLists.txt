cmake_minimum_required(VERSION 3.5)
project(tomatolang)


set(CMAKE_CXX_STANDARD 17)


# Find GNU readline library and header files
find_path(READLINE_INCLUDE_DIR NAMES readline/readline.h)
find_library(READLINE_LIBRARY readline)


set(SOURCE_FILES
        syntax/lexer.cpp
        syntax/lexer.hpp
        operators.cpp
        operators.hpp
        syntax/syntax_tree.cpp
        syntax/syntax_tree.hpp
        syntax/parser.cpp
        syntax/parser.hpp
        syntax/visitor.cpp
        syntax/visitor.hpp
        syntax/printer.cpp
        syntax/printer.hpp
        interpreter.cpp
        interpreter.hpp
        semantic/symtab.cpp
        semantic/symtab.hpp
        semantic/symbols.cpp
        semantic/symbols.hpp
        semantic/overloading.cpp semantic/overloading.hpp)


add_library(tomatolib ${SOURCE_FILES})
add_executable(tomato tomato.cpp)

target_include_directories(tomato PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(tomatolib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(tomatolib PUBLIC ${READLINE_INCLUDE_DIR})

target_link_libraries(tomato tomatolib ${READLINE_LIBRARY})
