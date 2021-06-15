#include "clientapp.h"
#include "imageprovider.h"
#include "iworld.h"
#include "mainmenumodel.h"

#include <QCoreApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <quasarapp.h>

#include <engine.h>
#include <qmlnotifyservice.h>
#include <QStandardPaths>
#include <QDir>
#include "pluginloader.h"
#include <viewsolutions.h>
#include "worldstatus.h"

#define PLUGINS_DIR QStandardPaths::

QByteArray ClientApp::initTheme() {
    int themeIndex = Settings::instance()->getValue(THEME, THEME_DEFAULT).toInt();

    switch (themeIndex) {
    case 1: return "Dark";
    default: return "Light";
    }

}

ClientApp::ClientApp() {
    _engine = new Engine();
    _menu = new MainMenuModel();

    connect(_menu, &MainMenuModel::sigNewGame, this , &ClientApp::start);
}

ClientApp::~ClientApp() {
    delete _menu;
    delete _engine;

    for (const auto& item : qAsConst(_availableLvls)) {
        delete item.viewModel;
        delete item.model;
    }

    _availableLvls.clear();
}

void ClientApp::initLang() {
    QLocale locale = QLocale::system();
    QString customLanguage = QuasarAppUtils::Params::getArg("lang");
    if(customLanguage.size()) {
        locale = QLocale(customLanguage);
    }

    if(!QuasarAppUtils::Locales::init(locale, {":/languages/languages/",
                                               ":/credits_languages/",
                                               ":/qmlNotify_languages/",
                                               ":/lv_languages/"})){
        QuasarAppUtils::Params::log("Error load language : " , QuasarAppUtils::Error);
    }
}

void ClientApp::initLvls() {
    auto plugins = availablePlugins();
    QList<QObject*> _availableWorlds;
    for (const auto& lvl: plugins) {
        WordlData data;
        IWorld* pluginData = PluginLoader::load(lvl.absoluteFilePath());

        if (pluginData) {

            data.model = pluginData;
            data.viewModel = new WorldViewData(data.model);
            _availableWorlds.push_back(data.viewModel);
            _availableLvls.insert(data.model->name(), data);
        }
    }

    _menu->setAvailableLvls(_availableWorlds);

}

IWorld *ClientApp::getLastWorld() {
    for (const auto &data : qAsConst(_availableLvls)) {
        if (data.viewModel && data.viewModel->unlocked()) {
            return data.model;
        }
    }

    return nullptr;
}

void ClientApp::start(const QString &lvl) {
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

    _engine->setWorld(data.model);
    _engine->start();
}

QList<QFileInfo> ClientApp::availablePlugins() const {
    QDir dir(QCoreApplication::applicationDirPath() + "/modules");
    auto list = dir.entryInfoList(QStringList() << "*.so" << "*.dll", QDir::Files);

    return list;
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

    initSnakeProjectResources();
    initLang();
    initLvls();

    engine->addImportPath(":/SnakeProjectModule/");


    if (!QmlNotificationService::init(engine)) {
        return false;
    }

    if (!ViewSolutions::init(engine)) {
        return false;
    }

    engine->load("qrc:/SnakeProjectModule/SnakeProject.qml");
    if (engine->rootObjects().isEmpty())
        return false;

    _engine->setWorld(getLastWorld());

    return true;
}
