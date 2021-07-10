//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "groundplate.h"
namespace JungleLvl {

GroundPlate::GroundPlate(): CRAWL::GroundTile("JungleGroundTile",
                                              "qrc:/qml/Models/Ground.qml") {
    setMash("#Cube");
    setSize({6, 6, 0.01});
    setBaseColorMap("qrc:/mesh/meshes/Other/Terrain_Base.jpg");
    setNormalMap("qrc:/mesh/meshes/Other/Terrain_Normal.jpg");
    setTiliesCount(6);

}

void GroundPlate::onIntersects(const IWorldItem *) {

}

int GroundPlate::tiliesCount() const {
    return _tiliesCount;
}

void GroundPlate::setTiliesCount(int newTiliesCount) {
    if (_tiliesCount == newTiliesCount)
        return;
    _tiliesCount = newTiliesCount;
    emit tiliesCountChanged();
}

}
