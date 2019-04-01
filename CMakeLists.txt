cmake_minimum_required(VERSION 3.8)
project(CLion)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp data/tree/AvlTree.tpp data/tree/AvlTree.h poly/dynamic/Base.h algo/Strings.cpp test/Tester.h test/Tester.cpp poly/dynamic/Base.cpp data/experiments/CaS.cpp data/experiments/CaS.h data/CaS.cpp data/CaS.h)
add_executable(CLion ${SOURCE_FILES})