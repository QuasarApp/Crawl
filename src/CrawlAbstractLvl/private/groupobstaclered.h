//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef GROUPOBSTACLERED_H
#define GROUPOBSTACLERED_H

#include "Crawl/layout.h"
#include "Crawl/clasteritem.h"

namespace AbstractLvl {

class GroupObstacleRed: public CRAWL::Layout, public CRAWL::IWorldItem {
public:
    GroupObstacleRed();

    // IRender interface
public:
    void render(unsigned int tbfMsec);
    void init();
};
}

#endif // GROUPOBSTACLERED_H
