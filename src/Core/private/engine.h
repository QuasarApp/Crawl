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
#include <Crawl/ilevel.h>

namespace CRAWL {

class IWorld;
class Store;
class StartData;
class User;
class StoreViewModel;
class MainMenuModel;

/**
 * @brief The Engine class
 */
class Engine : public QObject {

    Q_OBJECT
    Q_PROPERTY(QObject* player READ player NOTIFY playerChanged)
    Q_PROPERTY(QObject* world READ world NOTIFY worldChanged)
    Q_PROPERTY(QObject* nest READ nest NOTIFY worldChanged)

    Q_PROPERTY(QObject* scane READ scane WRITE setScane NOTIFY scaneChanged)
    Q_PROPERTY(QObject * menu READ menu NOTIFY menuChanged)


public:
    Engine(QObject * parent = nullptr);
    ~Engine();

    /**
     * @brief scane This method return main scane of the game.
     * @return pointer to main game scane.
     */
    Q_INVOKABLE QObject* scane();

    /**
     * @brief setLevel This method set new world level for game.
     * @param world This is pointer to new world level.
     */
    void setLevel(ILevel *world);

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

    /**
     * @brief currentUser This method return pointer too current user.
     * @return pointer too current user.
     */
    User *currentUser() const;

    /**
     * @brief initStore This method is wrapper of the Store::init method.
     * @param availabelItems This is list of available items.
     */
    void initStore(const QMultiHash<int, const IItem *> &availabelItems);

    /**
     * @brief store This pointer return pointer to store.
     * @return pointer to store.
     */
    Store *store() const;

    /**
     * @brief nest This method return pointer to the nest model.
     * @return pointer to the nest model.
     */
    QObject *nest() const ;

    /**
     * @brief menu This is a main menu model.
     * @return main menu model object.
     */
    QObject *menu() const;


signals:
    void scaneChanged();
    void playerChanged();
    void worldChanged();

    void menuChanged();

private slots:
    /**
     * @brief start This method run current lvl ( move prepared data from the nest to game world)
     * @param config This is confuguration that created new game world.
     * @return true if lvl started successful.
     */
    void start(const StartData &config) const;

    /**
     * @brief stop This slots invoked when world finished own session.
     */
    void stop() const;

private:
    void renderLoop();

    QObject *_scane = nullptr;
    ILevel* _currentLevel = nullptr;
    MainMenuModel *_menu = nullptr;

    quint64 _oldTimeRender = 0;

    User *_currentUser = nullptr;
    Store *_store = nullptr;

    QFuture<void> _renderLoopFuture;
    bool _renderLoop = false;
};

}
#endif // ENGINE_H
