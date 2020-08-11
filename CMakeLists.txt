cmake_minimum_required(VERSION 3.15)
project(Mine_Sweeping)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR  ON)
set(CMAKE_PREFIX_PATH "D:\\Productors\\Qt5\\5.14.1\\mingw73_64\\")

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(SOURCE_FILES
        main.cpp
        Core/unit.cpp
        Core/unit.h
        UI/Widget.cpp
        UI/Widget.h
        UI/GameGridButton.cpp
        UI/GameGridButton.h
        Core/board.cpp
        Core/board.h
        UI/GameWin.cpp
        UI/GameWin.h
        ConfigMgr/Configure.cpp
        ConfigMgr/Configure.h
        icon.rc
        )

add_executable(Mine_Sweeping ${SOURCE_FILES})

target_link_libraries(Mine_Sweeping Qt5::Widgets)