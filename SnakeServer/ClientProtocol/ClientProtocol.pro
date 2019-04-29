#
# Copyright (C) 2018 - 2019 QuasarApp.
# Distributed under the lgplv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

#-------------------------------------------------
#
# Project created by QtCreator 2019-02-12T11:08:54
#
#-------------------------------------------------

QT       -= gui
QT       += network

TARGET = ClientProtocol
TEMPLATE = lib

DEFINES += CLIENTPROTOCOL_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG(release, debug|release): {
    DESTDIR = $$PWD/build/release

} else {
    DESTDIR = $$PWD/build/debug
}

include($$PWD/../../QuasarAppLib/QuasarLib.pri)
include($$PWD/../../SnakeUtils/SnakeUtils.pri)


SOURCES += \
        basenetworkobject.cpp \
        clientprotocol.cpp \
        client.cpp \
        gamedata.cpp \
        getitem.cpp \
        login.cpp \
        networkclasssize.cpp \
        player.cpp \
        server.cpp \
        factorynetobjects.cpp \
        connectioninfo.cpp \
        updateplayerdata.cpp


HEADERS += \
        basenetworkobject.h \
        clientprotocol.h \
        clientprotocol_global.h \
        gamedata.h \
        getitem.h \
        login.h \
        networkclasssize.h \
        client.h \
        player.h \
        server.h \
        cp.h \
        config.h \
        factorynetobjects.h \
        connectioninfo.h \
        cpserver.h \
        updateplayerdata.h

