cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17 -lfreeimage)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(Capstone)

add_executable(Capstone src/main.cpp src/Utils.cpp src/SaveImage.cpp)
