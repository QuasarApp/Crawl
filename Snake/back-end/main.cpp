#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "controller.h"
#include "diff.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    //qmlRegisterType <Controller> ("Controller", 1, 0,"Controller");
    qmlRegisterType <GuiObject> ();
    qmlRegisterType <Diff> ();

    auto root = engine.rootContext();
    if (!root)
        return -1;

    Controller contr;
    root->setContextProperty("contr", &contr);

    engine.load(QUrl(QStringLiteral("qrc:/front-end/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
