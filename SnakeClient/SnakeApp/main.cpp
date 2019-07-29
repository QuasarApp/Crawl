#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <clientapp.h>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    ClientApp client;

    if (!client.init(&engine)) {
        return 1;
    }

    return app.exec();
}
