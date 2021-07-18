//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "absaluteplate.h"

namespace JungleLvl {

AbsalutePlate::AbsalutePlate(): CRAWL::IWorldItem(AUTO_CLASS_NAME) {
    setMash("#Cube");
    setSize({1000, 1000, 1});
    setColor("#000000");
}

void AbsalutePlate::onIntersects(const IWorldItem *) {}

void AbsalutePlate::render(unsigned int ) {
    setposition(getPlayer()->position() + QVector3D{0,0,-100});
}
}
