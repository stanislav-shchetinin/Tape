cmake_minimum_required(VERSION 3.22)
project(Yadro)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/libs)
add_executable(Yadro main.cpp)
