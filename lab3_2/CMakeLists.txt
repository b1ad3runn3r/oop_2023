cmake_minimum_required(VERSION 3.28)
project(lab3_2 CXX)

set(CMAKE_CXX_STANDARD 20)
find_package(Threads)

add_compile_options(-fsanitize=thread)
add_link_options(-fsanitize=thread)

add_subdirectory(src/Server/Packages)
add_subdirectory(src/Server/Message)
add_subdirectory(src/Server/Link)
add_subdirectory(src/Server/Server)
add_subdirectory(src/Server/TransportTable)
add_subdirectory(src/TableView)
add_subdirectory(tests)

add_executable(lab3_2 src/main.cpp)
target_link_libraries(lab3_2 PRIVATE
        transport_table
        packages
        message
        Threads::Threads)
