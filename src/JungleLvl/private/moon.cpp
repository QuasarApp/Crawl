//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#
#include "moon.h"

namespace JungleLvl {

Moon::Moon(const QVector3D* center):
    CRAWL::DayItem(center, AUTO_CLASS_NAME) {
    setColor("#6177ff");
    setLightForce(1100);
}

void Moon::init() {}

void Moon::onIntersects(const IWorldItem *) {}

}
