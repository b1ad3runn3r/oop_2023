cmake_minimum_required(VERSION 3.20)
project("Lab3" CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src/Vector)
add_subdirectory(tests/vector)

add_subdirectory(src/CPU/memory)
add_subdirectory(src/IDE)

add_executable(lab3 src/main.cpp)
target_link_libraries(lab3 memory)
