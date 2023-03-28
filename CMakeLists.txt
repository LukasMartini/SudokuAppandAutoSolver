cmake_minimum_required(VERSION 3.24)
project(WaveCollapseSudokuSolver)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(WaveCollapseSudokuSolver
        SudokuTable.cpp
        SudokuTable.h
        SudokuTableTests.cpp
)

add_subdirectory(googletest)
include_directories(googletest/googletest/include)
include_directories(googletest/googlemock/include)

#Link with GoogleTest
target_link_libraries(WaveCollapseSudokuSolver gtest gtest_main)

#Link with GoogleMock
target_link_libraries(WaveCollapseSudokuSolver gmock gmock_main)