#-------------------------------------------------
#
# Project created by QtCreator 2019-07-28T12:59:54
#
#-------------------------------------------------


TARGET = Client
TEMPLATE = lib

DEFINES += CLIENT_LIBRARY

QT += quick concurrent
CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    back-end/ProfileViewItems/mainmenumodel.h \
    back-end/ProfileViewItems/playerclientdata.h \
    back-end/asyncimageresponse.h \
    back-end/baseclass.h \
    back-end/clientapp.h \
    back-end/head.h \
    back-end/imageprovider.h \
    back-end/snake.h \
    back-end/controller.h \
    back-end/ProfileViewItems/userview.h \
    back-end/world.h \
    back-end/itemworld.h \
    back-end/box.h \
    back-end/guiobject.h \
    back-end/guiobjectfactory.h \
    back-end/diff.h \
    back-end/background.h \
    back-end/backgrounditem.h \
    client_global.h


SOURCES += \
    back-end/ProfileViewItems/mainmenumodel.cpp \
    back-end/ProfileViewItems/playerclientdata.cpp \
    back-end/asyncimageresponse.cpp \
    back-end/baseclass.cpp \
    back-end/clientapp.cpp \
    back-end/head.cpp \
    back-end/imageprovider.cpp \
    back-end/snake.cpp \
    back-end/controller.cpp \
    back-end/ProfileViewItems/userview.cpp \
    back-end/world.cpp \
    back-end/itemworld.cpp \
    back-end/box.cpp \
    back-end/guiobject.cpp \
    back-end/guiobjectfactory.cpp \
    back-end/diff.cpp \
    back-end/background.cpp \
    back-end/backgrounditem.cpp


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RESOURCES += qml.qrc


CONFIG(release, debug|release): {
    DESTDIR = $$PWD/build/release

} else {
    DESTDIR = $$PWD/build/debug
}

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

include($$PWD/../../QuasarAppLib/QuasarLib.pri)
include($$PWD/../../SnakeUtils/SnakeUtils.pri)
include($$PWD/../../SnakeServer/ClientProtocol/ClientProtocol.pri)

win32:RC_ICONS += img/icon.ico
