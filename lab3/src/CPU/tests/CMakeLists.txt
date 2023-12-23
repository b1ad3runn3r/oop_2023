find_package(Catch2 3 REQUIRED)

add_executable(lab3_vector_test test.cpp)
target_link_libraries(cpu_tests Catch2::Catch2WithMain)
