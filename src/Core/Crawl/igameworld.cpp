//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "igameworld.h"

#include <eventserver.h>

namespace CRAWL {

IGameWorld::IGameWorld() {
    _eventServer = new EventServer(this);

    connect(_eventServer, &EventServer::sigIntersect, this, &IWorld::onIntersects);
    connect(this, &IWorld::sigOBjctsListChanged, _eventServer, &EventServer::handleAvailableObjectChanges);

}

IGameWorld::~IGameWorld() {
    delete _eventServer;

}



}

