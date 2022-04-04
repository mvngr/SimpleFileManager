cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME SimpleFileManager)

project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Widgets QuickControls2 REQUIRED)

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

add_executable(${PROJECT_NAME} ${H_FILES} ${CPP_FILES} ${QRC_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Quick Qt5::Widgets Qt5::QuickControls2)

include (${PROJECT_SOURCE_DIR}/CPack.cmake)
install(
    TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION .
    DESTINATION .
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
    )
INSTALL(FILES ${PROJECT_SOURCE_DIR}/resources/${PROJECT_NAME}.desktop DESTINATION /usr/share/applications)
