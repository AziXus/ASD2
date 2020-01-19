cmake_minimum_required(VERSION 3.13)
project(Labo5)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wconversion -Wextra -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

add_executable(Labo5 main.cpp
        AVLTree.h
        BinarySearchTree.h TernarySearchTree.h Util.cpp Util.h)
