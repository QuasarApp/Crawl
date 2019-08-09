QT += quick concurrent
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
    back-end/ProfileViewItems/mainclient.cpp \
    back-end/ProfileViewItems/mainmenumodel.cpp \
    back-end/ProfileViewItems/networkclient.cpp \
    back-end/ProfileViewItems/playerclientdata.cpp \
    back-end/ProfileViewItems/settingsviewmodel.cpp \
    back-end/ProfileViewItems/userview.cpp \
    back-end/asyncimageresponse.cpp \
    back-end/background.cpp \
    back-end/backgrounditem.cpp \
    back-end/baseclass.cpp \
    back-end/box.cpp \
    back-end/clientapp.cpp \
    back-end/controller.cpp \
    back-end/diff.cpp \
    back-end/guiobject.cpp \
    back-end/guiobjectfactory.cpp \
    back-end/head.cpp \
    back-end/imageprovider.cpp \
    back-end/itemworld.cpp \
    back-end/settings.cpp \
    back-end/snake.cpp \
    back-end/world.cpp \
    back-end/main.cpp


TARGET = Snake


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

DISTFILES += \
    android/AndroidManifest.xml \
    android/AndroidManifest.xml \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew \
    android/gradlew \
    android/gradlew.bat \
    android/gradlew.bat \
    android/res/values/libs.xml \
    android/res/values/libs.xml \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    front-end/PagePopUp.qml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

RESOURCES += \
    qml.qrc

HEADERS += \
    back-end/ProfileViewItems/mainclient.h \
    back-end/ProfileViewItems/mainmenumodel.h \
    back-end/ProfileViewItems/networkclient.h \
    back-end/ProfileViewItems/playerclientdata.h \
    back-end/ProfileViewItems/settingsviewmodel.h \
    back-end/ProfileViewItems/userview.h \
    back-end/asyncimageresponse.h \
    back-end/background.h \
    back-end/backgrounditem.h \
    back-end/baseclass.h \
    back-end/box.h \
    back-end/clientapp.h \
    back-end/controller.h \
    back-end/diff.h \
    back-end/guiobject.h \
    back-end/guiobjectfactory.h \
    back-end/head.h \
    back-end/imageprovider.h \
    back-end/itemworld.h \
    back-end/settings.h \
    back-end/snake.h \
    back-end/world.h
