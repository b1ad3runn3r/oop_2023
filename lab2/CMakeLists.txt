cmake_minimum_required(VERSION 3.27)
project(lab2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

add_subdirectory(dice)
add_subdirectory(dialog)
add_subdirectory(tests)

add_executable(lab2 main.cpp)

target_link_libraries(lab2 dice)
target_link_libraries(lab2 dialog)
