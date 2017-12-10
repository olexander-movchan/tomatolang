cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(tomatolang)


set(CMAKE_CXX_STANDARD 14)


# Find GNU readline library and header files
find_path(READLINE_INCLUDE_DIR NAMES readline/readline.h)
find_library(READLINE_LIBRARY readline)


set(SOURCE_FILES
        lexer.cpp
        lexer.hpp
        )


add_library(tomatolib ${SOURCE_FILES})
add_executable(tomato tomato.cpp)

target_include_directories(tomato PRIVATE .)
target_include_directories(tomato PUBLIC ${READLINE_INCLUDE_DIR})
target_include_directories(tomatolib PRIVATE .)
target_include_directories(tomatolib PUBLIC ${READLINE_INCLUDE_DIR})

target_link_libraries(tomato tomatolib ${READLINE_LIBRARY})
