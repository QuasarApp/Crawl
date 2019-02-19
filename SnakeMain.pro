
TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS +=  \
        QuasarAppLib \
        SnakeUtils \
        Snake \
        SnakeServer \

QuasarAppLib.file = QuasarAppLib/QuasarApp.pro
Snake.file = Snake/snake.pro

include($$PWD/installer/installer.pri)


DISTFILES += \
    doc/librarymodel.qmodel \
    doc/calassdiagramm.qmodel
