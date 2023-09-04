cmake_minimum_required(VERSION 3.27)
project(lab1 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

add_library(sparse_matrix lib/matrix.cpp lib/matrix.h)
link_libraries(sparse_matrix)

add_executable(lab1 src/main.cpp)
