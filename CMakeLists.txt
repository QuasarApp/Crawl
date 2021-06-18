#
# Copyright (C) 2020-2021 QuasarApp.
# Distributed under the GPLv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

cmake_minimum_required(VERSION 3.14)
project(Crawl)
if(TARGET ${PROJECT_NAME})
  message("The ${PROJECT_NAME} arledy included in main Project")
  return()
endif()

include(submodules/QuasarAppLib/CMake/QuasarApp.cmake)

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

set(QT_VERSION_MAJOR 5)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Test REQUIRED)

if (NOT DEFINED CRAWL_TESTS)
    set(CRAWL_TESTS ON)
    message(1)

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
        message(2)
    endif()
endif()

# Add sub directories

if (ANDROID)
    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/Client/android")
endif()

add_subdirectory(submodules/QuasarAppLib)
add_subdirectory(submodules/SimpleQmlNotify)
add_subdirectory(submodules/ViewSolutions)

add_subdirectory(src/Core)
add_subdirectory(src/CrawlTestLvl)
add_subdirectory(src/CrawlAbstractLvl)

add_subdirectory(src/Client)


if (CRAWL_TESTS)
    add_subdirectory(tests)
else()
    message("The ${PROJECT_NAME} tests is disabled.")
endif()


initAll()

addDoc(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/doxygen.conf)
