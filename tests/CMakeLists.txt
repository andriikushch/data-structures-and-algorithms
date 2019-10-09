# Setup the minimum version required of CMake to generate the Makefile
cmake_minimum_required (VERSION 2.8)
# Raises a FATAL_ERROR if version < 2.8
cmake_minimum_required (VERSION 2.8 FATAL_ERROR)

add_executable(red_black_tree red_black_tree.cpp)