QT += testlib network sql
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \   
    tst_testsnakeserver.cpp

CONFIG(release, debug|release): {
    DESTDIR = $$PWD/build/release

} else {
    DESTDIR = $$PWD/build/debug
}

include($$PWD/../../QuasarAppLib/QuasarLib.pri)
include($$PWD/../ServerProtocol/ServerProtocol.pri)
include($$PWD/../ClientProtocol/ClientProtocol.pri)
include($$PWD/../../SnakeUtils/SnakeUtils.pri)
include($$PWD/../../SnakeServer/Server/Server.pri)


HEADERS +=
