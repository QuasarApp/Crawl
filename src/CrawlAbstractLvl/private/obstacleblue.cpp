//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "obstacleblue.h"
namespace AbstractLvl {

ObstacleBlue::ObstacleBlue() : IWorldItem(AUTO_CLASS_NAME) {
    setMash("qrc:/mesh/meshes/ObstacleBlue.mesh");
    setSize({1,1,1});
    setColor("#00bfff");
    setposition({250, 0, 200});
    setZ(0);
}

void ObstacleBlue::onIntersects(const IWorldItem *item) {
        Q_UNUSED(item);
}

}
