//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "obstaclered.h"

namespace AbstractLvl {

ObstacleRed::ObstacleRed() : CRAWL::ClasterItem(AUTO_CLASS_NAME) {
    setMash("qrc:/mesh/meshes/ObstacleRed.mesh");
    setSize({1,1,1});
    setColor("#ff1927");
    setZ(0);
}

}
