find_package(Catch2 3 REQUIRED)

file(GLOB_RECURSE TEST_SOURCES *.cpp)

add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests PRIVATE
        Catch2::Catch2WithMain
        packages
        message
        link
        server
        transport_table)

