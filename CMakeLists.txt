cmake_minimum_required(VERSION 3.8)
project(CLion)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp data/tree/AvlTree.tpp data/tree/AvlTree.h)
add_executable(CLion ${SOURCE_FILES})