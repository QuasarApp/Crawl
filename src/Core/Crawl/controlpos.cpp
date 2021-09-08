//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "controlpos.h"
#include "clasteritem.h"
#include <QtMath>

namespace CRAWL {

ControlPos::ControlPos() {

}

void ControlPos::add(ClasterItem *object) {

    Claster::add(object);
    updatePosition();

}

void ControlPos::remove(ClasterItem *object) {

    Claster::remove(object->guiId());
    updatePosition();

}

void ControlPos::changeLayout(const Refresh &fig) {
    _shape = fig;
}

void ControlPos::setDistance(int dist) {
    _distance = dist;
}

void ControlPos::updatePosition() {

    switch (_shape) {
        case CIRCLE:
            drawCircle();
            break;

        case SQUARE:
            drawSquare();
            break;

        case LINE:
            break;

        default:
            break;
     }

}

void ControlPos::drawCircle() {

    float step =  360 / objects().size();
    int temp = 1;

    for (ClasterItem* object: objects()) {

        float x = _distance * qCos(step*temp);
        float y = _distance * qSin(step*temp);
        GroupObject::updatePosition(object->guiId(), {x, y, 0});

        temp++;
    }

}

void ControlPos::drawSquare() {

    float step =  360 / objects().size();
    int temp = 1;

    for (ClasterItem* object: objects()) {

        float x = _distance * qCos(step*temp);
        float y = _distance * qSin(step*temp);
        GroupObject::updatePosition(object->guiId(), {x, y, 0});

        temp++;
    }

}

}
