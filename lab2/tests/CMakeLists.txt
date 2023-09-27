find_package(Catch2 2 REQUIRED)

add_executable(lab2_testing test.cpp)

target_link_libraries(lab2_testing dice Catch2::Catch2)
