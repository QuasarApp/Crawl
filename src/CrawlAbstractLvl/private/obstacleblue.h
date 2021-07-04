//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef OBJOBSTACLEBLUE_H
#define OBJOBSTACLEBLUE_H
#include "Crawl/iworlditem.h"


class ObstacleBlue: public IWorldItem {
public:
    ObstacleBlue();

    // IWorldItem interface
protected:
    void onIntersects(const IWorldItem *item) override;
};

#endif // OBJOBSTACLEBLUE_H
