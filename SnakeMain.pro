
TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS +=  \
        QuasarAppLib \
        Snake

QuasarAppLib.file = QuasarAppLib/QuasarApp.pro
Snake.file = Snake/snake.pro

include($$PWD/installer/installer.pri)
