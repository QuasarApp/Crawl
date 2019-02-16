QT += quick
CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    back-end/main.cpp \
    back-end/baseclass.cpp \
    back-end/head.cpp \
    back-end/snake.cpp \
    back-end/controller.cpp \
    back-end/world.cpp \
    back-end/itemworld.cpp \
    back-end/box.cpp \
    back-end/guiobject.cpp \
    back-end/lvls.cpp \
    back-end/guiobjectfactory.cpp \
    back-end/utils.cpp \
    back-end/diff.cpp \
    back-end/background.cpp \
    back-end/backgrounditem.cpp

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

include($$PWD/../QuasarAppLib/Etalons/qmake/install_prefix.pri)
include($$PWD/../QuasarAppLib/QuasarLib.pri)

install_data.files += $$QUASARAPP_LIB_OUTPUT_DIR/$$libfiletype
install_data.files += $$DESTDIR/$$runfiletype


HEADERS += \
    back-end/baseclass.h \
    back-end/head.h \
    back-end/snake.h \
    back-end/controller.h \
    back-end/world.h \
    back-end/itemworld.h \
    back-end/box.h \
    back-end/guiobject.h \
    back-end/utils.h \
    back-end/lvls.h \
    back-end/guiobjectfactory.h \
    back-end/diff.h \
    back-end/background.h \
    back-end/backgrounditem.h

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    front-end/PagePopUp.qml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

win32:RC_ICONS += img/icon.ico
