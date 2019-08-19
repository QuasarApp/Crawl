#include "clientapp.h"
#include "imageprovider.h"
#include "ProfileViewItems/userview.h"
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <back-end/ProfileViewItems/mainmenumodel.h>
#include <back-end/ProfileViewItems/notificationservice.h>

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
    qRegisterMetaType<NotificationData>("NotificationData");
    qRegisterMetaType<QList<NotificationData>> ("QList<NotificationData>");

    auto root = engine->rootContext();
    if (!root)
        return false;


    engine->addImageProvider(QLatin1String("userItems"), new ImageProvider());

    root->setContextProperty("contr", &contr);
    root->setContextProperty("notificationService", NotificationService::getService());

    engine->load(QUrl(QStringLiteral("qrc:/front-end/main.qml")));
    if (engine->rootObjects().isEmpty())
        return false;

    return true;
}
