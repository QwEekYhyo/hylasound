cmake_minimum_required(VERSION 3.16)

project(soundboard LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Multimedia)
qt_standard_project_setup()

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.hpp)

include_directories(include)

qt_add_executable(soundboard.exe ${SOURCES} ${HEADERS} resources/soundboard.qrc)

target_link_libraries(soundboard.exe PRIVATE Qt6::Widgets Qt6::Multimedia)

set_target_properties(soundboard.exe PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
