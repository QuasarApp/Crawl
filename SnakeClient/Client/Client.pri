#
# Copyright (C) 2018 - 2019 QuasarApp.
# Distributed under the lgplv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

!isEmpty(SERVER_LIB):error("Client.pri already included")
CLIENT_LIB = 1

#DEPENDS
CONFIG(release, debug|release): {
    CLIENT_LIB_OUTPUT_DIR="$$PWD/build/release"
} else {
    CLIENT_LIB_OUTPUT_DIR="$$PWD/build/debug"
}

LIBS += -L$$CLIENT_LIB_OUTPUT_DIR -lClient

include($$PWD/../../QuasarAppLib/QuasarLib.pri)
include($$PWD/../../SnakeUtils/SnakeUtils.pri)
include($$PWD/../../SnakeServer/ClientProtocol/ClientProtocol.pri)

INCLUDEPATH += "$$PWD"
INCLUDEPATH += "$$PWD/front-end"
INCLUDEPATH += "$$PWD/back-end"
#INCLUDEPATH += "$$PWD/back-end/ProfileViewItems"




