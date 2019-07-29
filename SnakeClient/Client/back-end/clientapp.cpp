#include "clientapp.h"
#include "ProfileViewItems/userview.h"
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <back-end/ProfileViewItems/mainmenumodel.h>

ClientApp::ClientApp() {

}

bool ClientApp::init(QQmlApplicationEngine *engine) {

    qmlRegisterType <GuiObject> ();
    qmlRegisterType <Diff> ();
    qmlRegisterType <MainMenuModel> ();
    qmlRegisterType <UserView> ();

    auto root = engine->rootContext();
    if (!root)
        return false;

    root->setContextProperty("contr", &contr);

    engine->load(QUrl(QStringLiteral("qrc:/front-end/main.qml")));
    if (engine->rootObjects().isEmpty())
        return false;

    return true;
}
