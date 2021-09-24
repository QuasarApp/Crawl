//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "layout.h"
#include "clasteritem.h"
#include <QtMath>

namespace CRAWL {

Layout::Layout() {

}

void Layout::add(ClasterItem *object) {

    Claster::add(object);
    updatePosition();

}

void Layout::remove(ClasterItem *object) {

    Claster::remove(object);
    updatePosition();

}

void Layout::changeLayout(const LayoutType &fig) {
    _shape = fig;
    updatePosition();
}

void Layout::setDistance(int dist) {
    _distance = dist;
    updatePosition();
}

void Layout::updatePosition() {

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

void Layout::drawCircle() {

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

void Layout::drawSquare() {

    if (objects().size() == 0) {
        QuasarAppUtils::Params::log(QString("The number of objects is zero. Add object."), QuasarAppUtils::Error);
        return;
    }

    int height = qFloor(qSqrt(objects().size()));
    int width = qFloor(objects().size() / height);

    int indObject = 0;
    for (auto idObj = objects().keyBegin(); idObj != objects().keyEnd(); idObj++) {

        float x = indObject % height;
        float y = qCeil(indObject  / height);

        GroupObject::updatePosition(*idObj, {(x * _distance) - (height  * _distance / 2),
                                            (y * _distance) - (width  * _distance / 2),
                                            0});
        indObject++;

    }

}

void Layout::drawLine() {

    if (objects().size() == 0) {
        QuasarAppUtils::Params::log(QString("The number of objects is zero. Add object."), QuasarAppUtils::Error);
        return;
    }

    float xObject = 0;
    float height =  objects().size() * _distance;

    for (ClasterItem* object: objects()) {
        GroupObject::updatePosition(object->guiId(), {xObject * _distance - (height / 2 * _distance), 0, 0});

        xObject++;
    }
}

}
