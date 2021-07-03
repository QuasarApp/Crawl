//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "plate.h"

Plate::Plate(): IGround("plate")
{
    setMash("qrc:/mesh/res/meshes/cube.mesh");
    setSize({100,100,0});
    setZ(0);
}

void Plate::onIntersects(const IWorldItem *item) {
    Q_UNUSED(item)
}
