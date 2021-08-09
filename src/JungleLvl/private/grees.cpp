//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "grees.h"

namespace JungleLvl {

Grees::Grees(): CRAWL::IWorldItem(AUTO_CLASS_NAME) {
    setMash("qrc:/mesh/meshes/Plant/Grass.mesh");
    setBaseColorMap("qrc:/mesh/meshes/Plant/Grass_Base.jpg");
    setSize({1,1,1});
    setRotation(QQuaternion::fromEulerAngles({0,0, static_cast<float>(rand() % 360)}));

}

}
