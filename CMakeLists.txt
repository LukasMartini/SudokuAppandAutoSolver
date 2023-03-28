cmake_minimum_required(VERSION 3.24)
project(WaveCollapseSedokuSolver)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(WaveCollapseSedokuSolver
        SedokuTable.cpp
        SedokuTable.h
        SedokuTableTests.cpp
)

add_subdirectory(googletest)
include_directories(googletest/googletest/include)
include_directories(googletest/googlemock/include)

#Link with GoogleTest
target_link_libraries(WaveCollapseSedokuSolver gtest gtest_main)

#Link with GoogleMock
target_link_libraries(WaveCollapseSedokuSolver gmock gmock_main)