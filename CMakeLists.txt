#
# Copyright (C) 2020-2021 QuasarApp.
# Distributed under the lgplv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

cmake_minimum_required(VERSION 3.14)
project(SnakeProject)
if(TARGET ${PROJECT_NAME})
  message("The ${PROJECT_NAME} arledy included in main Project")
  return()
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Test REQUIRED)

include(submodules/QuasarAppLib/CMake/QuasarApp.cmake)

if (NOT DEFINED SNAKEPROJECT_TESTS)
    set(SNAKEPROJECT_TESTS ON)

    if (DEFINED TARGET_PLATFORM_TOOLCHAIN)
        if (${TARGET_PLATFORM_TOOLCHAIN} STREQUAL "wasm32")
            set(SNAKEPROJECT_TESTS OFF)
        endif()
    endif()

    if (ANDROID)
        set(SNAKEPROJECT_TESTS OFF)
    endif()

    if (NOT QT_VERSION_MAJOR)
        set(SNAKEPROJECT_TESTS OFF)
    endif()
endif()

# Add sub directories

add_subdirectory(submodules/QuasarAppLib)
add_subdirectory(submodules/SimpleQmlNotify)

add_subdirectory(src/ClientLib)
add_subdirectory(src/Client)

if (SNAKEPROJECT_TESTS)
    add_subdirectory(tests)
else()
    message("The ${PROJECT_NAME} tests is disabled.")
endif()


initAll()

addDoc(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/doxygen.conf)
addDeployFromCustomFile("SnakeProject" "${CMAKE_CURRENT_SOURCE_DIR}/Deploy/SnakeProject.json")