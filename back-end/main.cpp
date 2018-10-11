#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "controller.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType <Controller> ("Controller", 1, 0,"Controller");
    qmlRegisterType <GuiObject> ("GuiObject", 1, 0, "GuiObject");

    engine.load(QUrl(QStringLiteral("qrc:/front-end/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
