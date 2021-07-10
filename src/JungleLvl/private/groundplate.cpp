//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "groundplate.h"
namespace JungleLvl {

GroundPlate::GroundPlate(): CRAWL::GroundTile("JungleGroundTile") {
    setMash("#Cube");
    setSize({10, 10, 0.01});
    setBaseColorMap("qrc:/mesh/meshes/Other/Terrain_Base.jpg");
    setNormalMap("qrc:/mesh/meshes/Other/Terrain_Normal.jpg");

}

void GroundPlate::onIntersects(const IWorldItem *) {

}

}
