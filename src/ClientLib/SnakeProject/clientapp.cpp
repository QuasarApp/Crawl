#include "clientapp.h"
#include "imageprovider.h"
#include "mainmenumodel.h"

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <quasarapp.h>

#include <qmlnotifyservice.h>

QByteArray ClientApp::initTheme() {
    int themeIndex = Settings::get()->getValue(THEME, THEME_DEFAULT).toInt();

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

    qmlRegisterType <GuiObject> ();
    qmlRegisterType <Diff> ();
    qmlRegisterType <MainMenuModel> ();
    qmlRegisterType <UserView> ();

    auto root = engine->rootContext();
    if (!root)
        return false;


    engine->addImageProvider(QLatin1String("userItems"), new ImageProvider());

    root->setContextProperty("contr", &contr);

    initLang();

    if (!QmlNotificationService::init(engine)) {
        return false;
    }

    engine->load(QUrl(QStringLiteral("qrc:/front-end/main.qml")));
    if (engine->rootObjects().isEmpty())
        return false;

    return true;
}
