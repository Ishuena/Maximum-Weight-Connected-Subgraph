cmake_minimum_required(VERSION 3.7)
project(basic_algo)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Vertex.cpp Vertex.h Vertices.h Vertices.cpp ColorSet.cpp ColorSet.h)
add_executable(basic_algo ${SOURCE_FILES})