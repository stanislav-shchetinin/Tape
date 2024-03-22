cmake_minimum_required(VERSION 3.22)
project(Yadro)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak,address -Wall -Wextra -Werror -Wpedantic")

include_directories(${CMAKE_SOURCE_DIR}/libs)

file(GLOB SUBDIRS "src/*")

foreach(dir ${SUBDIRS})
    if(IS_DIRECTORY ${dir})
        include_directories(${dir})
    endif()
endforeach()

add_executable(Yadro main.cpp
        src/config/config.h
        src/config/config.cpp
        src/tape/Tape.cpp
        src/tape/Tape.h
        src/sort/TapeSort.cpp
        src/sort/TapeSort.h
)
