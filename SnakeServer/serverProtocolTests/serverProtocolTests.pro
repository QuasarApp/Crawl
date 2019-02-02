QT += testlib network
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \ 
    tst_testserverprotockol.cpp

CONFIG(release, debug|release): {
    DESTDIR = $$PWD/build/release

} else {
    DESTDIR = $$PWD/build/debug
}

include($$PWD/../../QuasarAppLib/QuasarLib.pri)
include($$PWD/../ServerProtocol/ServerProtocol.pri)
