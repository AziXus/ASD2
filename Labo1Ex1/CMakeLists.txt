cmake_minimum_required(VERSION 3.13)
project(ASD1_Labo1Ex1)

set(CMAKE_CXX_STANDARD 11)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wconversion -Wextra -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

add_executable(ASD1_Labo1Ex1 ex1.cpp GraphFromImage.cpp GraphFromImage.h ParcoursEnProfondeur.h)