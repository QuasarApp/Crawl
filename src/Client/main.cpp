#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <SnakeProject/clientapp.h>


int main(int argc, char *argv[])
{

    QCoreApplication::setOrganizationName("QuasarApp");
    QCoreApplication::setApplicationName("Snake");

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    ClientApp client;

    if (!client.init(&engine)) {
        return 1;
    }

    return app.exec();
}
