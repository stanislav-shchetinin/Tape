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

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        tests
        tests/tape_tests.cc
        tests/config_test.cc
        tests/sort_test.cc
        src/config/config.h
        src/config/config.cpp
        src/tape/Tape.cpp
        src/tape/Tape.h
        src/sort/TapeSort.cpp
        src/sort/TapeSort.h
)
target_link_libraries(
        tests
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)