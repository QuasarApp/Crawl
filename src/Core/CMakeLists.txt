#
# Copyright (C) 2020-2021 QuasarApp.
# Distributed under the lgplv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

cmake_minimum_required(VERSION 3.14)
set(CURRENT_PROJECT "${PROJECT_NAME}Core")

add_definitions(-DSnakeProject_LIBRARY)


file(GLOB SOURCE_CPP
    "*SnakeProject/*.cpp"
     "private/*.cpp"
     "*.qrc"
     "SnakeProject/*.qrc"
     "private/*.qrc"
)

set(PUBLIC_INCUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(PRIVATE_INCUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/private")

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Quick3D Concurrent REQUIRED)

add_library(${CURRENT_PROJECT} ${SOURCE_CPP} ${SOURCE_QRC})

target_link_libraries(${CURRENT_PROJECT} PUBLIC
                        Qt${QT_VERSION_MAJOR}::Concurrent
                        QuasarApp
                        QmlNotyfyService)

target_include_directories(${CURRENT_PROJECT} PUBLIC ${PUBLIC_INCUDE_DIR})
target_include_directories(${CURRENT_PROJECT} PRIVATE ${PRIVATE_INCUDE_DIR})

set(LANGS ${CMAKE_CURRENT_SOURCE_DIR}/languages/en.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/ru.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/uk.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/ja.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/tr.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/zh.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/de.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/fr.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/es.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/pl.ts)

prepareQM(${CURRENT_PROJECT} ${CMAKE_CURRENT_SOURCE_DIR}/../ "${LANGS}")

set(QML_IMPORT_PATH ${QML_IMPORT_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/src" CACHE STRING "" FORCE)
