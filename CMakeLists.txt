cmake_minimum_required(VERSION 3.5)

project(k-editor LANGUAGES CXX)

set(PROJECT_NAME k-editor)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5Widgets REQUIRED)


add_executable(k
        main.cpp
        src/K.cpp
        src/Buffer.cpp
        src/LinumMode.cpp)

include_directories(src)

target_link_libraries(k Qt5::Widgets)
