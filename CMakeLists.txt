cmake_minimum_required(VERSION 3.10)
project(xghostclick)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "-pthread -ggdb3 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -pthread")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RELEASE)
endif ()

FILE(GLOB_RECURSE SOURCES source/*.cxx source/*.c++ source/*.C source/*.cpp source/*.cc)
add_executable(xghostclick ${SOURCES})
