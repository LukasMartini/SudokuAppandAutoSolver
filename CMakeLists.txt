cmake_minimum_required(VERSION 3.24)
project(WaveCollapseSudokuSolver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(.)

add_executable(WaveCollapseSudokuSolver
        SudokuTable.cpp SudokuTable.h SudokuTableTests.cpp
        InputWindow.cpp InputWindow.h WFC.cpp WFC.h main.cpp InputTable.cpp InputTable.h)

add_subdirectory(googletest)
include_directories(googletest/googletest/include)
include_directories(googletest/googlemock/include)

#Link with GoogleTest
target_link_libraries(WaveCollapseSudokuSolver gtest gtest_main)

#Link with GoogleMock
target_link_libraries(WaveCollapseSudokuSolver gmock gmock_main)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

target_link_libraries(WaveCollapseSudokuSolver Qt6::Core Qt6::Widgets)