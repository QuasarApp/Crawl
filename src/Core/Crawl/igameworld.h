//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef IGAMEWORLD_H
#define IGAMEWORLD_H


#include "iworld.h"

#include <gamesession.h>


namespace CRAWL {

/**
 * @brief The IGameWorld class Is world interface for view items on the game session.
 */
class IGameWorld : public IWorld
{
    Q_OBJECT
public:
    IGameWorld();
    ~IGameWorld();

private:
    GameSession _currentSession;
    EventServer * _eventServer = nullptr;

};

}
#endif // IGAMEWORLD_H
