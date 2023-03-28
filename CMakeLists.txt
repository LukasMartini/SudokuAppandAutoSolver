cmake_minimum_required(VERSION 3.24)
project(WaveCollapseSedokuSolver)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(WaveCollapseSedokuSolver
        SedokuTable.cpp
        SedokuTable.h)
