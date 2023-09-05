cmake_minimum_required(VERSION 3.27)
project(lab1 CXX)

set(CMAKE_CXX_STANDARD 20)

option(FUZZING "Enable ASAN to fuzz with AFL++" OFF)
if (FUZZING)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -fsanitize=address")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
endif(FUZZING)
unset(FUZZING CACHE)

add_library(sparse_matrix lib/matrix.cpp lib/matrix.h)
link_libraries(sparse_matrix)

add_executable(lab1 src/main.cpp)
