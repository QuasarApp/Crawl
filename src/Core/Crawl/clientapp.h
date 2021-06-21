//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef CLIENTAPP_H
#define CLIENTAPP_H

#include <QByteArray>
#include <QFileInfo>
#include <QStringList>
#include "global.h"

class Engine;
class IWorld;
class WorldViewData;
class QQmlApplicationEngine;
class MainMenuModel;
class IControl;

inline void initCrawlResources() { Q_INIT_RESOURCE(Crawl); }


/**
 * @brief The WordlData struct simple structure that contains information about world.
 */
struct WordlData {
    WorldViewData* viewModel = nullptr;
    IWorld * model = nullptr;
};


/**
 * @brief The ClientApp class This is main class of the Game engine.
 */
class CRAWL_EXPORT ClientApp : public QObject
{
    Q_OBJECT
public:
    ClientApp();
    ~ClientApp() override;

    /**
     * @brief init This method initialize engine on application.
     * @param engine This is qml engine instance object.
     * @return true if all initialize successful
     */
    bool init(QQmlApplicationEngine* engine);

private:
    QByteArray initTheme();
    void initLang();
    void initLvls();
    IWorld* getLastWorld();

    /**
     * @brief start This method star new game in @a lvl
     * @param lvl This is lvl name
     */
    void start(const QString& lvl);

    /**
     * @brief availablePlugins This method read all available plugins.
     * @return list of the available plugins.
     */
    QList<QFileInfo> availablePlugins() const;

    QHash<QString, WordlData> _availableLvls;
    MainMenuModel *_menu = nullptr;
    Engine *_engine = nullptr;
};

#endif // CLIENTAPP_H
