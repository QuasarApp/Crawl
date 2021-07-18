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
#include <abstractlvl.h>
#include <quasarapp.h>
#include <jungle.h>

void initLang() {
    QLocale locale = QLocale::system();
    QString customLanguage = QuasarAppUtils::Params::getArg("lang");
    if(customLanguage.size()) {
        locale = QLocale(customLanguage);
    }

    if(!QuasarAppUtils::Locales::init(locale, {":/crawlTranslations/languages/",
                                               ":/credits_languages/",
                                               ":/qmlNotify_languages/",
                                               ":/lv_languages/"})){
        QuasarAppUtils::Params::log("Error load language : ", QuasarAppUtils::Error);
    }
}

int main(int argc, char *argv[])
{

    QCoreApplication::setOrganizationName("QuasarApp");
    QCoreApplication::setApplicationName("Snake");

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    CRAWL::ClientApp client;

#ifdef QT_DEBUG
    client.registerLevel<TestLevel>();
#endif

    client.registerLevel<AbstractLvl>();
    client.registerLevel<Jungle>();

    if (!client.init(&engine)) {
        return 1;
    }

    initLang();

    return app.exec();
}
