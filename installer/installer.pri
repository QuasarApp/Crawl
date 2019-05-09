QT_DIR = $$dirname(QMAKE_QMAKE)
QML_DIR = $$PWD/../Snake/
DEPLOY_TARGET = $$PWD/../Snake/build/release
DEPLOY_SERVER = $$PWD/../SnakeServer/Daemon/build/release,$$PWD/../SnakeServer/Terminal/build/release


win32:LUPDATE = $$QT_DIR/lupdate.exe
win32:LRELEASE = $$QT_DIR/lrelease.exe

win32:DEPLOYER = cqtdeployer.exe

win32:OUT_FILE = SnakeInstaller.exe

contains(QMAKE_HOST.os, Linux):{
    LUPDATE = $$QT_DIR/lupdate
    LRELEASE = $$QT_DIR/lrelease

    DEPLOYER = cqtdeployer

    OUT_FILE = SnakeInstaller

}

BINARY_LIST
REPO_LIST
exists( $$QT_DIR/../../../Tools/QtInstallerFramework/3.0/bin/ ) {
      message( "QtInstallerFramework v3.0: yes" )
      BINARY_LIST += $$QT_DIR/../../../Tools/QtInstallerFramework/3.0/bin/binarycreator
      REPO_LIST += $$QT_DIR/../../../Tools/QtInstallerFramework/3.0/bin/repogen

}
exists( $$QT_DIR/../../../Tools/QtInstallerFramework/2.0/bin/ ) {
      message( "QtInstallerFramework v2.0: yes" )
      BINARY_LIST += $$QT_DIR/../../../Tools/QtInstallerFramework/2.0/bin/binarycreator
      REPO_LIST += $$QT_DIR/../../../Tools/QtInstallerFramework/2.0/bin/repogen
}

isEmpty (BINARY_LIST) {
      error( "QtInstallerFramework not found!" )
}

win32:EXEC=$$first(BINARY_LIST).exe

win32:REPOGEN=$$first(REPO_LIST).exe

contains(QMAKE_HOST.os, Linux):{
    unix:EXEC=$$first(BINARY_LIST)
    win32:EXEC=wine $$first(BINARY_LIST).exe

    REPOGEN=$$first(REPO_LIST)
}

message( selected $$EXEC and $$REPOGEN)


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

INSTALL_SERVER_DIR = ~/SnakeServer

BASE_DEPLOY_FLAGS = clear -qmake $$QMAKE_QMAKE -libDir $$PWD/../ -recursiveDepth 5
BASE_DEPLOY_FLAGS_SERVER = $$BASE_DEPLOY_FLAGS -targetDir $$INSTALL_SERVER_DIR
BASE_DEPLOY_FLAGS_SNAKE = $$BASE_DEPLOY_FLAGS -targetDir $$PWD/packages/Snake/data

deploy_dep.commands += $$DEPLOYER -bin $$DEPLOY_TARGET -qmlDir $$QML_DIR $$BASE_DEPLOY_FLAGS_SNAKE

mkpath( $$PWD/../Distro)

win32:CONFIG_FILE = $$PWD/config/configWin.xml
unix:CONFIG_FILE = $$PWD/config/configLinux.xml

deploy.commands = $$EXEC \
                       -c $$CONFIG_FILE \
                       -p $$PWD/packages \
                       $$PWD/../Distro/$$OUT_FILE

deploy.depends = deploy_dep

win32:ONLINE_REPO_DIR = $$ONLINE/Snake/Windows
unix:ONLINE_REPO_DIR = $$ONLINE/Snake/Linux

create_repo.commands = $$REPOGEN \
                        --update-new-components \
                        -p $$PWD/packages \
                        $$ONLINE_REPO_DIR

message( ONLINE_REPO_DIR $$ONLINE_REPO_DIR)
!isEmpty( ONLINE ) {

    message(online)

    release.depends = create_repo

    deploy.commands = $$EXEC \
                           --online-only \
                           -c $$CONFIG_FILE \
                           -p $$PWD/packages \
                           $$PWD/../Distro/$$OUT_FILE
}

OTHER_FILES += \
    $$PWD/config/*.xml \
    $$PWD/config/*.js \
    $$PWD/config/*.ts \
    $$PWD/config/*.css \
    $$PWD/packages/Installer/meta/* \
    $$PWD/packages/Installer/data/app.check \
    $$PWD/packages/Snake/meta/* \

installSnake.commands = $$DEPLOYER -bin $$DEPLOY_SERVER $$BASE_DEPLOY_FLAGS_SERVER

createLinks.commands = ln -sf $$INSTALL_SERVER_DIR/Terminal.sh ~/.local/bin/snake-term && \
                       ln -sf $$INSTALL_SERVER_DIR/SnakeServer-daemon.sh ~/.local/bin/snake-d


runServer.commands = snake-d daemon && echo daemon started

release.depends += installSnake
release.depends += createLinks
release.depends += runServer


QMAKE_EXTRA_TARGETS += \
    installSnake \
    createLinks \
    runServer \
    deploy_dep \
    deploy \
    create_repo \
    release \
