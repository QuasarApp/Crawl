#
# Copyright (C) 2021-2021 QuasarApp.
# Distributed under the GPLv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

cmake_minimum_required(VERSION 3.14)

set(CURRENT_PROJECT "${PROJECT_NAME}")

file(GLOB SOURCE_CPP
    "*.cpp"
     "private/*.cpp"
     "*.qrc"
     "private/*.qrc"
)

set(PUBLIC_INCUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

set(PRIVATE_INCUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/private")

qt_add_executable(${CURRENT_PROJECT} MANUAL_FINALIZATION ${SOURCE_CPP})

target_link_libraries(${CURRENT_PROJECT} PUBLIC ${PROJECT_NAME}Core TestLvl JungleLvl AbstractLvl)

target_include_directories(${CURRENT_PROJECT} PUBLIC ${PUBLIC_INCUDE_DIR})
target_include_directories(${CURRENT_PROJECT} PRIVATE ${PRIVATE_INCUDE_DIR})

SET(TARGET_DIR "${CMAKE_SOURCE_DIR}/Distro")
file(MAKE_DIRECTORY ${TARGET_DIR})

if (ANDROID)

#    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS AndroidExtras REQUIRED)

#    addDeployAPK(${CURRENT_PROJECT}
#                "${CMAKE_CURRENT_LIST_DIR}/android"
#                "SnakeProject"
#                "${SIGPATH}/Crawl.keystore"
#                "${SIGPASS_SNAKE}"
#                "${TARGET_DIR}"
#                "${SNAKE_EXTRA_LIBS}")

#    target_link_libraries(${CURRENT_PROJECT} PRIVATE Qt${QT_VERSION_MAJOR}::AndroidExtras)

    file(GLOB java_files
       "android/src/com/quasarapp/androidtools/*.java"
       "android/*.xml"
       "android/*.gradle"
       "android/gradlew"
       "android/gradle.*"

    )

    add_custom_target(${name}Android
        SOURCES ${java_files}
    )

else()
    # Desctop deploying
    addDeployFromCustomFile("Crawl"
                            "${CMAKE_CURRENT_SOURCE_DIR}/../../Deploy/Crawl.json")
endif()

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(${CURRENT_PROJECT})
    qt_finalize_executable(${CURRENT_PROJECT})
endif()

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
