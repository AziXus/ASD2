cmake_minimum_required(VERSION 3.13)
project(Labo2)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wconversion -Wextra -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

add_executable(Labo2
        DiGraph.cpp
        DiGraph.h
        DirectedCycle.h
        main.cpp
        ParcoursEnProfondeur.h
        SymbolGraph.h
        TopologicalSort.h
        Util.cpp
        Util.h)
