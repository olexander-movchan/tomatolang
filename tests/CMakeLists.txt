cmake_minimum_required(VERSION 3.5)
project(tomatotests)


set(CMAKE_CXX_STANDARD 17)


add_executable(tomatotest
        main.cpp
        lexer_tests.cpp
        parser_tests.cpp
        )

target_include_directories(tomatotest PUBLIC ${GTEST_INCLUDE_DIRS} ${CMAKE_HOME_DIRECTORY}/tomato/)
target_link_libraries(tomatotest tomatolib GTest::Main)
