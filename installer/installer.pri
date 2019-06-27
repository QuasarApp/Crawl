QT_DIR = $$QMAKESPEC/../../bin

QMAKE_BIN = $$QT_DIR/qmake
win32:QMAKE_BIN = $$QT_DIR/qmake.exe

message(QT_DIR = $$QT_DIR)

QML_DIR = $$PWD/../Snake/
DEPLOY_TARGET = $$PWD/../Snake/build/release
DEPLOY_SERVER = $$PWD/../SnakeServer/Daemon/build/release,$$PWD/../SnakeServer/Terminal/build/release

ANDROID_BUILD_DIR = $$PWD/../android-build

win32:LUPDATE = $$QT_DIR/lupdate.exe
win32:LRELEASE = $$QT_DIR/lrelease.exe

win32:DEPLOYER = %cqtdeployer%

win32:OUT_FILE = SnakeInstaller.exe

contains(QMAKE_HOST.os, Linux):{
    LUPDATE = $$QT_DIR/lupdate
    LRELEASE = $$QT_DIR/lrelease
    QMAKE_BIN = $$QT_DIR/qmake

    DEPLOYER = cqtdeployer

    OUT_FILE = SnakeInstaller

}

android {
    DEPLOYER = $$QT_DIR/androiddeployqt
}

BINARY_LIST
REPO_LIST

sopprted_versions = 3.1 3.0 2.0
for(val, sopprted_versions) {

    exists( $$QT_DIR/../../../Tools/QtInstallerFramework/$$val/bin/ ) {
          message( "QtInstallerFramework v$$val: yes" )
          BINARY_LIST += $$QT_DIR/../../../Tools/QtInstallerFramework/$$val/bin/binarycreator
          REPO_LIST += $$QT_DIR/../../../Tools/QtInstallerFramework/$$val/bin/repogen
    }
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

IGNORE_ENV=$$PWD/../Distro/,$$PWD/../deployTests,$$PWD/packages/Snake/data/
BASE_DEPLOY_FLAGS = clear -qmake $$QMAKE_BIN -libDir $$PWD/../ -recursiveDepth 5 -ignoreEnv $$IGNORE_ENV
BASE_DEPLOY_FLAGS_SERVER = $$BASE_DEPLOY_FLAGS -targetDir $$INSTALL_SERVER_DIR
BASE_DEPLOY_FLAGS_SNAKE = $$BASE_DEPLOY_FLAGS -targetDir $$PWD/packages/Snake/data

deploy_dep.commands += $$DEPLOYER -bin $$DEPLOY_TARGET -qmlDir $$QML_DIR $$BASE_DEPLOY_FLAGS_SNAKE

install_dep.commands = make INSTALL_ROOT=$$ANDROID_BUILD_DIR install

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

android {

    INPUT_ANDROID = --input $$PWD/../Snake/android-libsnake.so-deployment-settings.json
    OUTPUT_ANDROID = --output $$ANDROID_BUILD_DIR
    A_PL = --android-platform android-29
    JDK = --jdk /usr

    GRADLE = --gradle

    deploy_dep.commands = $$DEPLOYER $$INPUT_ANDROID $$OUTPUT_ANDROID $$A_PL $$JDK $$GRADLE
    deploy_dep.depends = install_dep

    deploy.commands = cp $$ANDROID_BUILD_DIR/build/outputs/apk/* $$PWD/../Distro
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


runDaemon.commands = snake-d daemon

unix:!Android:release.depends += installSnake
unix:!Android:release.depends += createLinks


QMAKE_EXTRA_TARGETS += \
    installSnake \
    createLinks \
    runDaemon \
    deploy_dep \
    install_dep \
    deploy \
    create_repo \
    release \
