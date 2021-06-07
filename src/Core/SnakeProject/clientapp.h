#ifndef CLIENTAPP_H
#define CLIENTAPP_H

#include <QByteArray>
#include <QFileInfo>
#include <QStringList>
#include "global.h"

class Engine;
class IWorld;

inline void initSnakeProjectResources() { Q_INIT_RESOURCE(SnakeProject); }

class QQmlApplicationEngine;

/**
 * @brief The ClientApp class This is main class of the Game engine.
 */
class SNAKEPROJECT_EXPORT ClientApp
{

public:
    ClientApp();
    virtual ~ClientApp();

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

    /**
     * @brief availablePlugins This method read all available plugins.
     * @return list of the available plugins.
     */
    QList<QFileInfo> availablePlugins() const;


    QHash<QString, IWorld*> _availableLvls;

    Engine *_engine = nullptr;
};

#endif // CLIENTAPP_H
