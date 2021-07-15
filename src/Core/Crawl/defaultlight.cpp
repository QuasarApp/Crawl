//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "defaultlight.h"

namespace CRAWL {

DefaultLight::DefaultLight(): IWorldLight(AUTO_CLASS_NAME) {
    setColor("#fff8e7");
    setposition({10000, 0, 10000});
    setRatation(QQuaternion::fromEulerAngles({0,0,-90}));
    setLightForce(110);
}

void DefaultLight::render(unsigned int) {

}

void DefaultLight::init() {

}

void DefaultLight::onIntersects(const IWorldItem *) {

}
}
