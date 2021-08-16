//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "clientapp.h"
#include "imageprovider.h"
#include "iworld.h"
#include "mainmenumodel.h"

#include <QCoreApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <quasarapp.h>
#include <store.h>

#include <engine.h>
#include <qmlnotifyservice.h>
#include <QStandardPaths>
#include <QDir>
#include "pluginloader.h"
#include <viewsolutions.h>
#include "worldstatus.h"
#include "user.h"

namespace CRAWL {


QByteArray ClientApp::initTheme() {
    int themeIndex = Settings::instance()->getValue(THEME, THEME_DEFAULT).toInt();

    switch (themeIndex) {
    case 1: return "Dark";
    default: return "Light";
    }
}


ClientApp::ClientApp() {
    _engine = new Engine();
}

ClientApp::~ClientApp() {
    delete _engine;
}

bool ClientApp::init(QQmlApplicationEngine *engine) {

    qputenv("QT_QUICK_CONTROLS_MATERIAL_THEME", initTheme());
    qputenv("QT_QUICK_CONTROLS_STYLE", "Material");

    auto root = engine->rootContext();
    if (!root)
        return false;

    engine->addImageProvider(QLatin1String("userItems"), new ImageProvider());

    root->setContextProperty("engine", QVariant::fromValue(_engine));

    qmlRegisterUncreatableMetaObject(
                WorldStatus::staticMetaObject,
                "engine.worldstatus",
                1, 0,
                "WorldStatus",
                "Error: only enums");

    initCrawlResources();

    engine->addImportPath(":/CrawlModule/");


    if (!QmlNotificationService::init(engine)) {
        return false;
    }

    if (!ViewSolutions::init(engine)) {
        return false;
    }

    engine->load("qrc:/CrawlModule/Crawl.qml");
    if (engine->rootObjects().isEmpty())
        return false;

    _engine->init();

    return true;
}

void ClientApp::addLvl(ILevel *levelWordl) {
    _engine->addLvl(levelWordl);
}

}
