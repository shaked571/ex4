cmake_minimum_required(VERSION 3.7)
project(ex4)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        CacheFS.h check.cpp)

add_executable(ex4 ${SOURCE_FILES})