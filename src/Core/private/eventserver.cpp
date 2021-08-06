//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "eventserver.h"

#include <Crawl/iworlditem.h>
#include <Crawl/iworld.h>
#include <QtConcurrent>

namespace CRAWL {

EventServer::EventServer(IWorld *instance) {
    debug_assert(instance, "Invalid World pointer in EventServer");
    _worldInstance = instance;

    _supportedEventsKeys = {Events::Intersects};
}

EventServer::~EventServer() {
    stop();
}

void EventServer::start() {
    if (_renderLoopFuture.isRunning())
        return;

    _renderLoop = true;
    _renderLoopFuture = QtConcurrent::run([this](){renderLoop();});
}

void EventServer::stop() {
    _renderLoop = false;
    _renderLoopFuture.waitForFinished();
}

void EventServer::handleAvailableObjectChanges(const Diff &diff) {
    for (int added: diff.addedIds) {
        auto obj = _worldInstance->getItem(added);

        if (!obj->isDecorative()) {
            continue;
        }

        for (int event: qAsConst(_supportedEventsKeys)) {
            addToSupportedEvents(obj, event);
        }

        _objects.insert(obj->guiId(), obj);
    }

    for (int removed: diff.removeIds) {
        for (int event: qAsConst(_supportedEventsKeys)) {
            _supportedEvents[event].remove(removed);
        }
        _objects.remove(removed);
    }
}

void EventServer::eventProcess() {
    for (auto it  = _supportedEvents.begin(); it != _supportedEvents.end(); ++it) {
        for (const IWorldItem* item : qAsConst(it.value())) {

            switch (it.key()) {

            case Events::Intersects : {
                QList<const IWorldItem*> result;
                for (const IWorldItem *object : qAsConst(_objects)) {
                    if (item != object && item->intersects(*object)) {
                        result.append(object);
                    }
                }

                if (result.size()) {
                    emit sigIntersect(result << item);
                }
                break;
            }

            default: {
                QuasarAppUtils::Params::log("Not supported event", QuasarAppUtils::Error);
            }

            }
        }
    }
}

void EventServer::addToSupportedEvents(const IWorldItem * obj, int event) {
    if (obj->isSopportEvent(event)) {
        _supportedEvents[event].insert(obj->guiId(), obj);
    };
}

void EventServer::renderLoop() {
    while (_renderLoop) {
        quint64 currentTime = QDateTime::currentMSecsSinceEpoch();

        if (!_oldTimeRender) {
            _oldTimeRender = currentTime;
            continue;
        }

        eventProcess();
        int waitTime = 100 - currentTime + _oldTimeRender;
        _oldTimeRender = currentTime;

        if (waitTime > 0)
            std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
    }
}
}
