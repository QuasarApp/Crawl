
TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS +=  \
        QuasarAppLib \
        SnakeUtils \
        SnakeClient \
        SnakeServer \

QuasarAppLib.file = QuasarAppLib/QuasarApp.pro
Snake.file = Snake/snake.pro

include($$PWD/installer/installerSnake.pri)
include($$PWD/test.pri)

DISTFILES += \
    doc/librarymodel.qmodel \
    doc/calassdiagramm.qmodel
