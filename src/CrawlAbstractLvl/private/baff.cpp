//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "baff.h"

Baff::Baff() : IWorldItem("Baff") {
    setMash("qrc:/mesh/meshes/Baff.mesh");
    setSize({1,1,1});
    setZ(0);
}

void Baff::onIntersects(const IWorldItem *item) {
        Q_UNUSED(item);
}
