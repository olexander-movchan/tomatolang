cmake_minimum_required(VERSION 3.5)
project(tomatolang)

add_subdirectory(tomatotools)

option(TOMATO_BUILD_DOC "Generate Doxygen documentation" ON)
option(TOMATO_BUILD_TESTS "Build GTest based tests" ON)

find_package(GTest)
if (GTEST_FOUND)
    add_subdirectory(tests)
endif ()

find_package(Doxygen)
if (DOXYGEN_FOUND AND TOMATO_BUILD_DOC)
    add_custom_target(tomato_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM )
elseif(TOMATO_BUILD_DOC)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND AND TOMATO_BUILD_DOC)
