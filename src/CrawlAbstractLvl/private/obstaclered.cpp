//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "obstaclered.h"

namespace AbstractLvl {

ObstacleRed::ObstacleRed() : IWorldItem(AUTO_CLASS_NAME) {
    setMash("qrc:/mesh/meshes/ObstacleRed.mesh");
    setSize({2,2,2});
    setColor("#ff1927");
    setZ(0);
}

void ObstacleRed::onIntersects(const IWorldItem *item) {
        Q_UNUSED(item);
}

}
