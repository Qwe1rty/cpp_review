cmake_minimum_required(VERSION 3.8)
project(CLion)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp data/tree/avl_tree.cpp data/tree/avl_tree.h)
add_executable(CLion ${SOURCE_FILES})