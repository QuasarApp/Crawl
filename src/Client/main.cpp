//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <Crawl/clientapp.h>
#include <testlevel.h>
#include <jungle.h>


int main(int argc, char *argv[])
{

    QCoreApplication::setOrganizationName("QuasarApp");
    QCoreApplication::setApplicationName("Snake");

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    CRAWL::ClientApp client;

    client.registerLevel<TestLevel>();
    client.registerLevel<Jungle>();

    if (!client.init(&engine)) {
        return 1;
    }
    return app.exec();
}
