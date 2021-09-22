//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "obstaclerebitem.h"
#include "groupobstaclered.h"

namespace AbstractLvl {

GroupObstacleRed::GroupObstacleRed(): CRAWL::IWorldItem(AUTO_CLASS_NAME) {

    setDistance(20);
    changeLayout(CRAWL::LayoutType::LINE);

    for(int i(0); i < 4; i++)   {
        add(new ObstacleRebItem);
    }

}

void GroupObstacleRed::render(unsigned int tbfMsec) {
    Layout::render(tbfMsec);
    IWorldItem::render(tbfMsec);
}

void GroupObstacleRed::init() {

}

}
