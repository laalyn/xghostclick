cmake_minimum_required(VERSION 3.19)
project(xghostclick)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RELEASE)
endif ()

FILE(GLOB_RECURSE SOURCES src/*.cpp src/*.cxx src/*.c++ src/*.cc src/*.C)
add_executable(xghostclick ${SOURCES})
add_executable(example-runner runners/src/example.cxx)
