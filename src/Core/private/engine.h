//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef ENGINE_H
#define ENGINE_H

#include <QFuture>
#include <QObject>
#include <QQmlEngine>
#include <Crawl/diff.h>

namespace CRAWL {

class IWorld;
class Store;

/**
 * @brief The Engine class
 */
class Engine : public QObject {

    Q_OBJECT
    Q_PROPERTY(QObject* player READ player NOTIFY playerChanged)
    Q_PROPERTY(QObject* world READ world NOTIFY worldChanged)

    Q_PROPERTY(QObject* scane READ scane WRITE setScane NOTIFY scaneChanged)
    Q_PROPERTY(QObject* menu READ menu WRITE setMenu NOTIFY menuChanged)
    Q_PROPERTY(int _prepareLvlProgress READ prepareLvlProgress WRITE setPrepareLvlProgress NOTIFY prepareLvlProgressChanged)

public:
    Engine(QObject * parent = nullptr);
    ~Engine();

    /**
     * @brief scane This method return main scane of the game.
     * @return pointer to main game scane.
     */
    Q_INVOKABLE QObject* scane();

    /**
     * @brief setQmlEngine This method sets qml engine
     * @param newEngine This is pointer to the qml engine.
     */
    void setQmlEngine(QQmlEngine *newEngine);

    /**
     * @brief setWorld This method set new world for game.
     * @param world This is pointer to new world.
     */
    void setWorld(IWorld *world);

    /**
     * @brief setScane This method sets new scane object. The scane object are
     * @param newScane are Qt Quick 3d node object form qml.
     */
    void setScane(QObject *newScane);

    /**
     * @brief currentWorld return pointer to current world object.
     * @return raw pointer to current world object.
     */
    IWorld *currentWorld() const;

    /**
     * @brief player return player object.
     * @return player object
     */
    QObject* player() const;

    /**
     * @brief world return player object.
     * @return world object
     */
    QObject* world() const;

    /**
     * @brief menu This method return pointer to cistom menu.
     * @return pointer to custom menu.
     * @note menu creating in the Wolrld object.
     */
    QObject *menu() const;

    /**
     * @brief setMenu This method sets new menu object.
     * @param newMenu
     */
    void setMenu(QObject *newMenu);

    /**
     * @brief prepareLvlProgress This method return rurrent progress of the loading lvl.
     * @return current progress of loading new level on the world. progress range is 0 - 100 
     */
    int prepareLvlProgress() const;

    /**
     * @brief start This method run current lvl
     * @return true if lvl started successful.
     */
    bool start() const;

    /**
     * @brief getGameObject This method using in qml for getting main model of the gui objects.
     * @param id This is id of the gui object.
     * @return pointer to game object model
     */
    Q_INVOKABLE QObject *getGameObject(int id) const;

    /**
     * @brief startRenderLoop This method start render loop in engine.
     */
    void startRenderLoop();

    /**
     * @brief stopRenderLoop This method stop render loop in engine.
     */
    void stopRenderLoop();

    /**
     * @brief isRendering This method erturn true if the render loop is working else false.
     * @return true if the render loop is working else false.
     */
    bool isRendering() const;

signals:
    void scaneChanged();
    void playerChanged();
    void worldChanged();

    void menuChanged();
    void prepareLvlProgressChanged();

private:
    void setPrepareLvlProgress(int newPrepareLvlProgress);
    bool prepareNewWorld();
    void renderLoop();


    QObject *_scane = nullptr;
    QQmlEngine *_engine = nullptr;
    IWorld* _currentWorld = nullptr;
    QObject *_menu = nullptr;
    int _prepareLvlProgress;

    quint64 _oldTimeRender = 0;

    QFuture<void> _renderLoopFuture;
    bool _renderLoop = false;
};

}
#endif // ENGINE_H
