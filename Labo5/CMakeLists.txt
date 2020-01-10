cmake_minimum_required(VERSION 3.13)
project(Labo5 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(Labo5
        AVLTree.h
        BinarySearchTree.h)
