cmake_minimum_required(VERSION 3.5)
project(tomato)


add_subdirectory(src)


find_package(GTest)
if (GTEST_FOUND)
    add_subdirectory(tests)
endif ()


find_package(Doxygen)
if (DOXYGEN_FOUND)
    add_custom_target(tomato_doxygen EXCLUDE_FROM_ALL
            COMMAND ${DOXYGEN_EXECUTABLE}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM )
elseif(TOMATO_BUILD_DOC)
    message("Doxygen doesn't found, install and reload cmake project to generate docs.")
endif (DOXYGEN_FOUND)
