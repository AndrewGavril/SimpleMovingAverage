cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 17)
project(SimpleMovingAverage)
include_directories(${PROJECT_SOURCE_DIR})

add_executable(SimpleMovingAverageTest ./src/main_simple_test.cpp)
add_executable(SimpleMovingAveragePerfTest ./src/main_perf_test.cpp)
