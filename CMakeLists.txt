cmake_minimum_required(VERSION 2.8)

list( APPEND CMAKE_CXX_FLAGS "-fopenmp -std=c++14 ${CMAKE_CXX_FLAGS}")

project(LeProject)


include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(bin/test ${SOURCES})
