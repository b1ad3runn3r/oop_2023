find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Gui)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Charts)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(ide
        src/app.cpp
        src/TableViewer/TableViewer.cpp
        src/TableViewer/TableViewer.h
        src/TableViewer/TableViewer.ui
        src/Calculations.cpp
        src/Calculations.hpp)

target_link_libraries(ide PUBLIC
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Charts
        packages
        message
        transport_table)
