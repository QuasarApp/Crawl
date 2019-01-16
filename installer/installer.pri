QT_DIR = $$dirname(QMAKE_QMAKE)
QML_DIR = $$PWD/../Snake
DEPLOY_TARGET_ALL = $$PWD/../Snake/build/release,$$PWD/../SnakeServer/Daemon/build/release,$$PWD/../SnakeServer/Client/build/release,$$PWD/../SnakeServer/ServerProtocol/build/release,$$PWD/../QuasarAppLib/build/release
DEPLOY_TARGET_SNAKE = $$PWD/../Snake/build/release,$$PWD/../QuasarAppLib/build/release
DEPLOY_TARGET_SERVER = $$PWD/../SnakeServer/Daemon/build/release,SnakeServer/Client/build/release,$$PWD/../SnakeServer/ServerProtocol/build/release,$$PWD/../QuasarAppLib/build/release

LUPDATE = $$QT_DIR/lupdate
LRELEASE = $$QT_DIR/lrelease

win32:DEPLOYER = $$PWD/../CQtDeployerBinaries/Windows/cqtdeployer.exe
unix:DEPLOYER = $$PWD/../CQtDeployerBinaries/Linux/cqtdeployer.sh

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

BASE_DEPLOY_FLAGS= clear -qmake $$QMAKE_QMAKE -targetDir $$PWD/packages/Snake/data

deploy_depends_all.commands += $$DEPLOYER -bin $$DEPLOY_TARGET_ALL $$BASE_DEPLOY_FLAGS  -qmlDir $$QML_DIR
deploy_depends_server.commands += $$DEPLOYER -bin $$DEPLOY_TARGET_SERVER $$BASE_DEPLOY_FLAGS
deploy_depends_snake.commands += $$DEPLOYER -bin $$DEPLOY_TARGET_SNAKE $$BASE_DEPLOY_FLAGS -qmlDir $$QML_DIR

create_installer.commands = $$EXEC \
                               -c $$PWD/config/config.xml \
                               -p $$PWD/packages \
                               $$PWD/$$OUT_FILE

create_installer_all.commands = $$EXEC \
                               -c $$PWD/config/config.xml \
                               -p $$PWD/packages \
                               $$PWD/$$OUT_FILE

create_installer_snake.commands = $$EXEC \
                               -c $$PWD/config/config.xml \
                               -p $$PWD/packages \
                               $$PWD/$$OUT_FILE

create_installer_server.commands = $$EXEC \
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

create_installer_all.depends = deploy_depends_all
create_installer_snake.depends = deploy_depends_snake
create_installer_server.depends = deploy_depends_server

QMAKE_EXTRA_TARGETS += \
    deploy_depends_all \
    deploy_depends_snake \
    deploy_depends_server \
    create_installer_all \
    create_installer_snake \
    create_installer_server
