#
# Copyright (C) 2021-2021 QuasarApp.
# Distributed under the GPLv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

cmake_minimum_required(VERSION 3.14)
set(CURRENT_PROJECT "TestLvl")

add_definitions(-DCRAWL_LIBRARY)

file(GLOB SOURCE_CPP
    "*.cpp"
     "private/*.cpp"
     "*.qrc"
     "private/*.qrc"
)

set(PUBLIC_INCUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(PRIVATE_INCUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/private")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../Client/modules)

add_library(${CURRENT_PROJECT} ${SOURCE_CPP})

target_link_libraries(${CURRENT_PROJECT} PUBLIC ${PROJECT_NAME}Core)

target_include_directories(${CURRENT_PROJECT} PUBLIC ${PUBLIC_INCUDE_DIR})
target_include_directories(${CURRENT_PROJECT} PRIVATE ${PRIVATE_INCUDE_DIR})
