
TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS +=  \
        QuasarAppLib \
        CQtDeployer \
        Snake

QuasarAppLib.file = QuasarAppLib/QuasarApp.pro
Snake.file = Snake/snake.pro
Snake.depends = QuasarAppLib CQtDeployer

include($$PWD/installer/installer.pri)
