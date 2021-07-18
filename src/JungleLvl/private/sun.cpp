//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "sun.h"

namespace JungleLvl {

Sun::Sun(const QVector3D* center):
    CRAWL::DayItem(center, AUTO_CLASS_NAME) {
    setColor("#f8d850");
    setLightForce(5100);
}

void Sun::onIntersects(const IWorldItem *) {}

void Sun::init() {}

}
