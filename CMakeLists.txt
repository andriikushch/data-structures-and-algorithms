# Setup the minimum version required of CMake to generate the Makefile
cmake_minimum_required (VERSION 2.8)
# Raises a FATAL_ERROR if version < 2.8
cmake_minimum_required (VERSION 2.8 FATAL_ERROR)

project (data-structures-and-algoritms)

SET(CMAKE_CXX_FLAGS "-std=c++11")

set (LEARN_CMAKE_VERSION_MAJOR 0)
set (LEARN_CMAKE_VERSION_MINOR 0)
set (LEARN_CMAKE_VERSION_PATCH 1)

IF(NOT EXISTS ${PROJECT_SOURCE_DIR}/tests/catch.hpp)
    file(DOWNLOAD https://github.com/catchorg/Catch2/releases/download/v2.9.2/catch.hpp ${PROJECT_SOURCE_DIR}/tests/catch.hpp)
ENDIF()

add_subdirectory(data-structures/binary_tree)
add_subdirectory(data-structures/red_black_tree)
add_subdirectory(data-structures/linked_list)
add_subdirectory(data-structures/queue)
add_subdirectory(data-structures/stack)
add_subdirectory(tests)