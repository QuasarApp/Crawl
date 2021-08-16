//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include <QFuture>
#include <QObject>

#include <Crawl/diff.h>
#include <QMultiHash>


#ifndef EVENTSERVER_H
#define EVENTSERVER_H

namespace CRAWL {

class IWorldItem;
class IWorld;

/**
 * @brief The EventServer class process all game events.
 * This class process all game events on the separate thread and do not change the game objects. All signal of the events return constant object pointers.
*/
class EventServer: public QObject
{
    Q_OBJECT
public:
    EventServer(IWorld * instance);
    ~EventServer();

    /**
     * @brief start This method start a processing og the objects events.
     */
    void start();

    /**
     * @brief stop This method stop the processing of the objects.
     */
    void stop();

public slots:
    /**
     * @brief handleAvailableObjectChanges This slots handle all changes of the world.
     * @param diff This is changes on the world.
     */
    void handleAvailableObjectChanges(const Diff& diff);

signals:
    /**
     * @brief sigIntersect This signal emit when objects intersect on the world.
     * @param trigger This is pointer to object that support this evvent.
     * @param objects This is list of the intersects objects.
     */
    void sigIntersect(const IWorldItem* trigger, QList<const IWorldItem*> objects);

private:
    void eventProcess();
    void addToSupportedEvents(const IWorldItem *obj, int event);

    void renderLoop();

    IWorld * _worldInstance = nullptr;
    QHash<int, const IWorldItem*> _objects;
    QHash<int, QHash<int, const IWorldItem*>> _supportedEvents;
    QList<int> _supportedEventsKeys;
    QFuture<void> _renderLoopFuture;
    bool _renderLoop = false;
    quint64 _oldTimeRender = 0;

};

}

#endif // EVENTSERVER_H
