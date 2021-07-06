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
#include "ilevel.h"

class QQmlApplicationEngine;
inline void initCrawlResources() { Q_INIT_RESOURCE(Crawl); }

namespace CRAWL {


class Engine;
class IWorld;
class WorldViewData;
class MainMenuModel;
class IControl;


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

    template<class LevelType>

    /**
     * @brief registerLevel This method register new levels in game.
     */
    void registerLevel() {

        static_assert(std::is_base_of_v<ILevel, LevelType>,
                "Plrease use the child classes of the ILevel interface for tegistering new levels in the crawl game.");

        addLvl(LevelType().world());
    }

private:
    QByteArray initTheme();
    IWorld* getLastWorld();

    /**
     * @brief addLvl This method should be add level to game.
     * @param levelWordl This is world instance
     */
    void addLvl(IWorld* levelWordl);

    /**
     * @brief start This method star new game in @a lvl
     * @param lvl This is lvl name
     */
    void start(const QString& lvl);

    QHash<QString, WordlData> _availableLvls;
    MainMenuModel *_menu = nullptr;
    Engine *_engine = nullptr;
};

}

#endif // CLIENTAPP_H
