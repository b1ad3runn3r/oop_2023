find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Gui)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(ide
        src/app.cpp
        src/config.h
        src/notepad.cpp
        src/notepad.h
        src/notepad.ui
        src/notepad.qrc)

target_link_libraries(ide
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets)
