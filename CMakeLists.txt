cmake_minimum_required(VERSION 3.22)

project(SimpleMovingAverage)
include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
)
add_executable(SimpleMovingAverageTest src/main.cpp)