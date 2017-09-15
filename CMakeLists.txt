cmake_minimum_required(VERSION 3.5)
project(tomatolang)

add_subdirectory(tomatotools)

find_package(GTest)

if (GTEST_FOUND)
    add_executable(tomatotest tests/main.cpp tests/lexer_tests.cpp)
    target_include_directories(tomatotest PUBLIC ${GTEST_INCLUDE_DIRS} tomatotools)
    target_link_libraries(tomatotest tomatolib GTest::Main)
endif ()
