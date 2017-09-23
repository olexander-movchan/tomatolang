cmake_minimum_required(VERSION 3.5)
project(tomatolang)

add_subdirectory(tomatotools)

find_package(GTest)
if (GTEST_FOUND)
    add_subdirectory(tests)
endif ()
