//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "controlpos.h"

namespace CRAWL {

ControlPos::ControlPos() {

}

void ControlPos::add(ClasterItem *object) {

    GroupObject::updatePosition();

}

void ControlPos::remove(ClasterItem *object) {

    GroupObject::updatePosition();

}

void ControlPos::changeLayout(const _Figure &fig) {

    if (fig == CIRCLE) {
        GroupObject::updatePosition();
    }

    if (fig == SQUARE) {
        GroupObject::updatePosition();
    }

    if (fig == LINE) {
        GroupObject::updatePosition();
    }

}

}
