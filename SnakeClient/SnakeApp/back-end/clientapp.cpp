#include "clientapp.h"
#include "imageprovider.h"
#include "ProfileViewItems/userview.h"
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <back-end/ProfileViewItems/mainmenumodel.h>

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

    engine->load(QUrl(QStringLiteral("qrc:/front-end/main.qml")));
    if (engine->rootObjects().isEmpty())
        return false;

    return true;
}
