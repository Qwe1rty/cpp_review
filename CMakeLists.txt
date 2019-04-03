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
        poly/dynamic/Base.h
        poly/dynamic/Base.cpp
        data/misc/CaS.cpp
        data/misc/CaS.h)
add_executable(CLion ${SOURCE_FILES})