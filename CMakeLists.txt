cmake_minimum_required(VERSION 3.22)
project(Yadro)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak,address -Wall -Wextra -Werror -Wpedantic")

include_directories(${CMAKE_SOURCE_DIR}/libs ${CMAKE_SOURCE_DIR}/src/tape ${CMAKE_SOURCE_DIR}/src/config)
add_executable(Yadro main.cpp
        src/config/config.h
        src/config/config.cpp
        src/tape/Tape.cpp
        src/tape/Tape.h)
