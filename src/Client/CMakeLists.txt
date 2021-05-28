#
# Copyright (C) 2021-2021 QuasarApp.
# Distributed under the lgplv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

cmake_minimum_required(VERSION 3.14)

set(CURRENT_PROJECT "${PROJECT_NAME}")

file(GLOB SOURCE_CPP
    "*.cpp"
     "private/*.cpp"
)

if (${QT_VERSION_MAJOR})
    file(GLOB SOURCE_QRC
        "*.qrc"
        "private/*.qrc"
    )

endif()

set(PUBLIC_INCUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

set(PRIVATE_INCUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/private")


if (ANDROID)
    add_library(${CURRENT_PROJECT} ${SOURCE_CPP} ${SOURCE_QRC})
else()
    add_executable(${CURRENT_PROJECT} ${SOURCE_CPP} ${SOURCE_QRC})
endif()

target_link_libraries(${CURRENT_PROJECT} PUBLIC ${PROJECT_NAME}Core)

target_include_directories(${CURRENT_PROJECT} PUBLIC ${PUBLIC_INCUDE_DIR})
target_include_directories(${CURRENT_PROJECT} PRIVATE ${PRIVATE_INCUDE_DIR})

SET(TARGET_DIR "${CMAKE_SOURCE_DIR}/Distro")
file(MAKE_DIRECTORY ${TARGET_DIR})



if (ANDROID)
    set(SNAKE_EXTRA_LIBS "${PROJECT_NAME}Core"
                         QuasarApp
                         QmlNotyfyService)

    find_package(QT NAMES Qt6 Qt5 COMPONENTS AndroidExtras REQUIRED)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS AndroidExtras REQUIRED)

    addDeployAPK(${CURRENT_PROJECT}
                "${CMAKE_CURRENT_LIST_DIR}/android"
                "SnakeProject"
                "${SIGPATH}/SnakeProject.keystore"
                "${SIGPASS_SNAKE}"
                "${TARGET_DIR}"
                "${SNAKE_EXTRA_LIBS}")

    target_link_libraries(${CURRENT_PROJECT} PRIVATE Qt${QT_VERSION_MAJOR}::AndroidExtras)

else()
    # Desctop deploying
    addDeployFromCustomFile("SnakeProject"
                            "${CMAKE_CURRENT_SOURCE_DIR}/../../Deploy/SnakeProject.json")
endif()
