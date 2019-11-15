cmake_minimum_required(VERSION 3.13)
project(Labo3)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wconversion -Wextra -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

add_executable(Labo3
        EdgeWeightedDigraph.h
        EdgeWeightedGraph.h
        EdgeWeightedGraphCommon.h
        main.cpp
        MinimumSpanningTree.h
        ShortestPath.h
        TrainNetwork.cpp
        TrainNetwork.h
        UnionFind.cpp
        UnionFind.h
        Util.cpp
        Util.h TrainDiGraphWrapper.h
        TrainGraphWrapper.cpp TrainGraphWrapper.h)
