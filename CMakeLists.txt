cmake_minimum_required(VERSION 3.8)
project(CLion)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        main.cpp
        data/tree/AvlTree.tpp
        data/tree/AvlTree.h
        algo/Strings.cpp
        test/Tester.h
        test/Tester.tpp
        poly/dynamic/Basic.h
        poly/dynamic/Basic.cpp
        data/misc/CaS.cpp
        data/misc/CaS.h
        data/misc/SFINAE.tpp
        data/misc/SFINAE.h
        algo/TwoPointers.h
        algo/TwoPointers.cpp
        algo/DynamicProgramming.h algo/DynamicProgramming.cpp data/misc/Initialization.cpp)
add_executable(CLion ${SOURCE_FILES})