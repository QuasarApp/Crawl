#
# Copyright (C) 2020-2021 QuasarApp.
# Distributed under the GPLv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

cmake_minimum_required(VERSION 3.14)
set(CURRENT_PROJECT "${PROJECT_NAME}Core")

add_definitions(-DCRAWL_LIBRARY)

file(GLOB SOURCE_CPP
    "Crawl/*.cpp"
    "Extensions/*.cpp"
     "private/*.cpp"
     "*.qrc"
     "Crawl/*.qrc"
     "private/*.qrc"
)

set(PUBLIC_INCUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(PRIVATE_INCUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/private")

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Quick3D Gui Concurrent REQUIRED)

add_library(${CURRENT_PROJECT} ${SOURCE_CPP} ${SOURCE_QRC})

target_link_libraries(${CURRENT_PROJECT} PUBLIC
                        Qt${QT_VERSION_MAJOR}::Concurrent
                        Qt${QT_VERSION_MAJOR}::Quick3D
                        Qt${QT_VERSION_MAJOR}::Gui
                        QuasarApp
                        QmlNotyfyService
                        ViewSolutions)

target_include_directories(${CURRENT_PROJECT} PUBLIC ${PUBLIC_INCUDE_DIR})
target_include_directories(${CURRENT_PROJECT} PRIVATE ${PRIVATE_INCUDE_DIR})

set(QML_IMPORT_PATH ${QML_IMPORT_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/" CACHE STRING "" FORCE)
