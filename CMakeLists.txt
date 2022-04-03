cmake_minimum_required(VERSION 3.14)

set(PRJ_NAME SimpleFileManager)

project(${PRJ_NAME} LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick Widgets QuickControls2 REQUIRED)

file(GLOB H_FILES
    ${PROJECT_SOURCE_DIR}/src/*.h
    ${PROJECT_SOURCE_DIR}/src/models/*.h
    )

file(GLOB CPP_FILES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/models/*.cpp
    )

file(GLOB QRC_FILES
    ${PROJECT_SOURCE_DIR}/resources/*.qrc
    )

add_executable(${PRJ_NAME} ${H_FILES} ${CPP_FILES} ${QRC_FILES})

target_link_libraries(${PRJ_NAME} PRIVATE Qt5::Core Qt5::Quick Qt5::Widgets Qt5::QuickControls2)

