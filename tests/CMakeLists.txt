cmake_minimum_required(VERSION 3.5)
project(tomatotests)

add_executable(tomatotest
        main.cpp
        lexer_tests.cpp
        parser_tests.cpp
        interpreter_tests.cpp
        )

target_include_directories(tomatotest PUBLIC ${GTEST_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/tomatotools/)
target_link_libraries(tomatotest tomatolib GTest::Main)
