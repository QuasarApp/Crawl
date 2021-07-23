#
# Copyright (C) 2020-2021 QuasarApp.
# Distributed under the GPLv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

cmake_minimum_required(VERSION 3.14)
project(Crawl VERSION 0.1 LANGUAGES CXX)

if(TARGET ${PROJECT_NAME})
  message("The ${PROJECT_NAME} arledy included in main Project")
  return()
endif()

if (ANDROID)
    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/Client/android")
endif()

find_package(QT NAMES Qt5 Qt6 COMPONENTS Core REQUIRED)
include(submodules/QuasarAppLib/CMake/QuasarApp.cmake)

if (${QT_VERSION_MAJOR} LESS_EQUAL 5)
    message("The ${PROJECT_NAME} support only qt6. please rebuild this project with qt6")
    initAll()
    return()
endif()

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Test REQUIRED)


if (DEFINED TARGET_PLATFORM_TOOLCHAIN)
    if (${TARGET_PLATFORM_TOOLCHAIN} STREQUAL "wasm32")
        initAll()
        return()
    endif()
endif()


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(BUILD_SHARED_LIBS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if (NOT DEFINED CRAWL_TESTS)
    set(CRAWL_TESTS ON)

    if (DEFINED TARGET_PLATFORM_TOOLCHAIN)
        if (${TARGET_PLATFORM_TOOLCHAIN} STREQUAL "wasm32")
            set(CRAWL_TESTS OFF)
        endif()
    endif()

    if (ANDROID)
        set(CRAWL_TESTS OFF)
    endif()

    if (NOT QT_VERSION_MAJOR)
        set(CRAWL_TESTS OFF)
    endif()
endif()

# Add sub directories

add_subdirectory(submodules/QuasarAppLib)
add_subdirectory(submodules/SimpleQmlNotify)
add_subdirectory(submodules/ViewSolutions)

add_subdirectory(src/Core)
add_subdirectory(src/CrawlTestLvl)
add_subdirectory(src/CrawlAbstractLvl)
add_subdirectory(src/JungleLvl)

add_subdirectory(src/Client)


if (CRAWL_TESTS)
    add_subdirectory(tests)
else()
    message("The ${PROJECT_NAME} tests is disabled.")
endif()


initAll()

addDoc(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/doxygen.conf)
