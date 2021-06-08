#include "clientapp.h"
#include "imageprovider.h"
#include "iworld.h"
#include "mainmenumodel.h"

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <quasarapp.h>

#include <engine.h>
#include <qmlnotifyservice.h>
#include <QStandardPaths>
#include <QDir>
#include "pluginloader.h"

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
}

ClientApp::~ClientApp() {
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

    for (const auto& lvl: plugins) {
        WordlData data;

        data.model = PluginLoader::load(lvl.absoluteFilePath());
        if (data.model) {
            data.viewModel = new WorldViewData(data.model);
            _availableLvls.insert(data.model->name(), data);
        }
    }
}

QList<QFileInfo> ClientApp::availablePlugins() const {
    QDir dir(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
    auto list = dir.entryInfoList(QStringList() << "*.so" << "*.dll", QDir::Files);

    return list;
}

bool ClientApp::init(QQmlApplicationEngine *engine) {

    qputenv("QT_QUICK_CONTROLS_MATERIAL_THEME", initTheme());
    qputenv("QT_QUICK_CONTROLS_STYLE", "Material");

    qmlRegisterAnonymousType<MainMenuModel>("MainMenuModel", 1);

    auto root = engine->rootContext();
    if (!root)
        return false;

    engine->addImageProvider(QLatin1String("userItems"), new ImageProvider());

    root->setContextProperty("engine", QVariant::fromValue(_engine));
    initSnakeProjectResources();
    initLang();
    initLvls();

    engine->addImportPath(":/SnakeProjectModule/");

    if (!QmlNotificationService::init(engine)) {
        return false;
    }

    engine->load("qrc:/SnakeProjectModule/SnakeProject.qml");
    if (engine->rootObjects().isEmpty())
        return false;

    return true;
}
