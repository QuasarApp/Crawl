QT_DIR = $$dirname(QMAKE_QMAKE)
QML_DIR = $$PWD/../NoisierGui/QML
QT_BASE_DIR = $$QT_DIR/../
LUPDATE = $$QT_DIR/lupdate
LRELEASE = $$QT_DIR/lrelease

WINDEPLOY = $$QT_DIR/windeployqt.exe

OUT_FILE = installer

CONFIG(serverbuild): {
    EXEC = binarycreator
} else: {

    BINARY_LIST
    exists( $$QT_DIR/../../../Tools/QtInstallerFramework/3.0/bin/ ) {
          message( "QtInstallerFramework v3.0: yes" )
          BINARY_LIST += $$QT_DIR/../../../Tools/QtInstallerFramework/3.0/bin/binarycreator
    }
    exists( $$QT_DIR/../../../Tools/QtInstallerFramework/2.0/bin/ ) {
          message( "QtInstallerFramework v2.0: yes" )
          BINARY_LIST += $$QT_DIR/../../../Tools/QtInstallerFramework/2.0/bin/binarycreator
    }

    isEmpty (BINARY_LIST) {
          error( "QtInstallerFramework not found!" )
    }

    EXEC=$$first(BINARY_LIST)
    message( selected $$EXEC  )

}

win32 {
    LUPDATE = $${LUPDATE}.exe
    LRELEASE = $${LRELEASE}.exe
    EXEC = $${EXEC}.exe
    OUT_FILE = $${OUT_FILE}.exe
}

SUPPORT_LANGS = ru

defineReplace(findFiles) {
    patern = $$1
    path = $$2

    all_files = $$files(*$${patern}, true)
    win32:all_files ~= s|\\\\|/|g
    win32:path ~= s|\\\\|/|g

    for(file, all_files) {
        result += $$find(file, $$path)
    }

    return($$result)
}

XML_FILES = $$files(*.xml, true)

for(LANG, SUPPORT_LANGS) {
    for(XML, XML_FILES) {
        FILE_PATH = $$dirname(XML)

        JS_FILES = $$findFiles(".js", $$FILE_PATH)
        UI_FILES = $$findFiles(".ui", $$FILE_PATH)

        commands += "$$LUPDATE $$JS_FILES $$UI_FILES -ts $$FILE_PATH/$${LANG}.ts"
        TS_FILES += $$FILE_PATH/$${LANG}.ts

    }

    for(TS, TS_FILES) {
        commands += "$$LRELEASE $$TS"
    }
}

for(command, commands) {
    system($$command)|error("Failed to run: $$command")
}


win32:deploy_depends.commands = $$WINDEPLOY --qmldir $$QML_DIR $$PWD/packages/Noisier/data/NoisierStart.exe & $$WINDEPLOY --qmldir $$QML_DIR $$PWD/packages/Noisier/data/NoisierDevice.dll


unix:deploy_depends.commands = python \
                             $$PWD/linuxQtDeploy.py \
                             $$PWD/packages/Noisier/data/NoisierStart \
                             --qt-base-dir  $$QT_BASE_DIR \
                             --qml-scan-dir $$QML_DIR

create_installer.commands = $$EXEC \
                               -c $$PWD/config/config.xml \
                               -p $$PWD/packages \
                               $$PWD/$$OUT_FILE

OTHER_FILES += \
    $$PWD/config/config.xml \
    $$PWD/config/controlScript.js \
    $$PWD/config/ru.ts \
    $$PWD/config/style.css \
    $$PWD/packages/Installer/meta/installscript.js \
    $$PWD/config/config.xml \
    $$PWD/packages/Installer/meta/package.xml \
    $$PWD/packages/Installer/data/app.check \
    $$PWD/packages/Installer/meta/ru.ts \
    $$PWD/linuxQtDeploy.py \
    $$PWD/packages/Installer/meta/targetwidget.ui \
    $$PWD/packages/Snake/meta/package.xml \
    $$PWD/packages/Snake/meta/installscript.js \
    $$PWD/packages/Snake/meta/ru.ts


QMAKE_EXTRA_TARGETS += \
    deploy_depends \
    create_installer
