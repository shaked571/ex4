cmake_minimum_required(VERSION 3.6)
project(ex4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES check.cpp CacheFS.h CacheFS.cpp Algorithm.cpp Algorithm.h CacheAlgorithm.cpp CacheAlgorithm.h Block.cpp Block.h)
add_executable(ex4 ${SOURCE_FILES})


