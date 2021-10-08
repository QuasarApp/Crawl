//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef OBSTACLEREBITEM_H
#define OBSTACLEREBITEM_H

#include "obstaclered.h"

namespace AbstractLvl {

class ObstacleRebItem: public ObstacleRed {
public:
    ObstacleRebItem();

    // IRender interface
public:
    void render(unsigned int tbfMsec);
};

}

#endif // OBSTACLEREBITEM_H
