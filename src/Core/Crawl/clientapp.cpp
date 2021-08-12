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

ILevel *ClientApp::getLastLevel() {
    for (const auto &data : qAsConst(_availableLvls)) {
        if (data.model && data.model->world() && _engine->currentUser() &&
                _engine->currentUser()->isUnlocked(data.model->world()->itemId())) {
            return data.model;
        }
    }

    return nullptr;
}

ClientApp::ClientApp() {
    _engine = new Engine();
    _menu = new MainMenuModel();

    connect(_menu, &MainMenuModel::sigLevelChanged, this, &ClientApp::changeLevel);
}

ClientApp::~ClientApp() {
    delete _menu;
    delete _engine;

    for (auto it = _availableLvls.begin(); it != _availableLvls.end(); ++it) {
        delete it.value().viewModel;
        delete it.value().model;
    }

    _availableLvls.clear();
}

void ClientApp::initStore(Store *store) {
    QMultiHash<int, const IItem *> storeItems;
    for (const auto &data : qAsConst(_availableLvls)) {
        if (data.model && data.model->world())
            storeItems.unite(data.model->world()->childItemsRecursive());
    }

    store->init(storeItems);
}

void ClientApp::changeLevel(int lvl) {
    WordlData data = _availableLvls.value(lvl);

    if (!data.model) {
        QuasarAppUtils::Params::log("Failed to start lvl.", QuasarAppUtils::Error);
        return;
    }

    if (!_engine) {
        QuasarAppUtils::Params::log("Failed to start lvl, Engine not initialized.",
                                    QuasarAppUtils::Error);

        return;
    }

    _engine->setLevel(data.model);
}

bool ClientApp::init(QQmlApplicationEngine *engine) {

    qputenv("QT_QUICK_CONTROLS_MATERIAL_THEME", initTheme());
    qputenv("QT_QUICK_CONTROLS_STYLE", "Material");

    auto root = engine->rootContext();
    if (!root)
        return false;

    engine->addImageProvider(QLatin1String("userItems"), new ImageProvider());

    root->setContextProperty("engine", QVariant::fromValue(_engine));
    root->setContextProperty("mainmenu", QVariant::fromValue(_menu));

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

    _engine->setLevel(getLastLevel());
    _engine->setQmlEngine(engine);
    initStore(_engine->store());

    return true;
}

void ClientApp::addLvl(ILevel *levelWordl) {
    WordlData data;

    data.model = levelWordl;
    data.viewModel = new WorldViewData(data.model->world());
    _availableLvls.insert(data.model->world()->itemId(), data);
    _menu->addWorldViewModel(data.viewModel);
}

}
