#
# Copyright (C) 2018 - 2019 QuasarApp.
# Distributed under the lgplv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

!isEmpty(SNAKEUTILS_LIB):error("SnakeUtils.pri already included")
SNAKEUTILS_LIB = 1

#DEPENDS
CONFIG(release, debug|release): {
    SNAKEUTILS_LIB_OUTPUT_DIR="$$PWD/build/release"
} else {
    SNAKEUTILS_LIB_OUTPUT_DIR="$$PWD/build/debug"
}

LIBS += -L$$SNAKEUTILS_LIB_OUTPUT_DIR -lSnakeUtils

INCLUDEPATH += "$$PWD/"



