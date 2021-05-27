#include "clientapp.h"
#include "imageprovider.h"
#include "SnakeProject/mainmenumodel.h"

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <quasarapp.h>

#include <qmlnotifyservice.h>

QByteArray ClientApp::initTheme() {
    int themeIndex = Settings::instance()->getValue(THEME, THEME_DEFAULT).toInt();

    switch (themeIndex) {
    case 1: return "Dark";
    default: return "Light";
    }

}

ClientApp::ClientApp() {
}

ClientApp::~ClientApp() {
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

bool ClientApp::init(QQmlApplicationEngine *engine) {

    qputenv("QT_QUICK_CONTROLS_MATERIAL_THEME", initTheme());
    qputenv("QT_QUICK_CONTROLS_STYLE", "material");

    qmlRegisterAnonymousType<GuiObject>("GuiObject", 1);
    qmlRegisterAnonymousType<Diff>("Diff", 1);
    qmlRegisterAnonymousType<MainMenuModel>("MainMenuModel", 1);

    auto root = engine->rootContext();
    if (!root)
        return false;

    engine->addImageProvider(QLatin1String("userItems"), new ImageProvider());

    root->setContextProperty("contr", &contr);
    initSnakeProjectResources();
    initLang();

    engine->addImportPath(":/SnakeProjectModule/");

    if (!QmlNotificationService::init(engine)) {
        return false;
    }

    engine->load("qrc:/SnakeProjectModule/SnakeProject.qml");
    if (engine->rootObjects().isEmpty())
        return false;

    return true;
}
