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

    Claster::remove(object);
    updatePosition();

}

void ControlPos::changeLayout(const Refresh &fig) {
    _shape = fig;
    updatePosition();
}

void ControlPos::setDistance(int dist) {
    _distance = dist;
    updatePosition();
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
            drawLine();
            break;

        default:
            break;
     }

}

void ControlPos::drawCircle() {

    if (objects().size() == 0) {
        QuasarAppUtils::Params::log(QString("The number of objects is zero. Add object."), QuasarAppUtils::Error);
        return;
    }

    float step =  360 / objects().size();
    int temp = 0;

    for (ClasterItem* object: objects()) {

        float x = _distance * qCos(step*temp);
        float y = _distance * qSin(step*temp);
        GroupObject::updatePosition(object->guiId(), {x, y, 0});

        temp++;
    }

}

void ControlPos::drawSquare() {

    if (objects().size() == 0) {
        QuasarAppUtils::Params::log(QString("The number of objects is zero. Add object."), QuasarAppUtils::Error);
        return;
    }

    int height = qFloor(qSqrt(objects().size()));

    int indObject = 0;
    for (auto idObj = objects().keyBegin(); idObj != objects().keyEnd(); idObj++) {

        int x = indObject % height;
        int y = qCeil(indObject  / height);

        GroupObject::updatePosition(idObj, {x + _distance,
                                            y + _distance,
                                            0});
        indObject++;

    }

}

void ControlPos::drawLine() {

    if (objects().size() == 0) {
        QuasarAppUtils::Params::log(QString("The number of objects is zero. Add object."), QuasarAppUtils::Error);
        return;
    }

    float xObject = 0;
    for (ClasterItem* object: objects()) {
        GroupObject::updatePosition(object->guiId(), {xObject + _distance, 0, 0});

        xObject++;
    }
}

}
