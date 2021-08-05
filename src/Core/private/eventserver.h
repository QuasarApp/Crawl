//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef EVENTSERVER_H
#define EVENTSERVER_H

namespace CRAWL {

class IWorldItem;

/**
 * @brief The EventServer class process all game events.
 */
class EventServer
{
public:
    EventServer();

    /**
     * @brief process This method process al events of an @a item object
     * @param item This is processed object.
     */
    void process(IWorldItem* item);
};

}

#endif // EVENTSERVER_H
