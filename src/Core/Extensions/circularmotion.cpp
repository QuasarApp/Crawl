//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "circularmotion.h"

#include <Crawl/guiobject.h>
#include "cmath"

namespace CRAWL {

CircularMotion::CircularMotion(const QVector3D *center) {
    _center = center;
}

void CircularMotion::render(unsigned int tbfMsec) {
    if (auto _this = checkminimumRequariedType<GuiObject>()) {
        if (!_center)
            return;

        double motionCoef = 360 / (2 * M_PI * radius());
        _angle += motionCoef * angularVelocity() * (tbfMsec / 1000.f);

        _this->setposition(*_center + (QQuaternion().fromAxisAndAngle(_axis, _angle).rotatedVector({0,0,0}).normalized() * radius()));
    }
}

float CircularMotion::angularVelocity() const {
    return _angularVelocity;
}

void CircularMotion::setAngularVelocity(float newAngularVelocity) {
    _angularVelocity = newAngularVelocity;
}

const QVector3D &CircularMotion::axis() const {
    return _axis;
}

void CircularMotion::setAxis(const QVector3D &newAxis) {
    _axis = newAxis;
}

float CircularMotion::radius() const {
    return _radius;
}

void CircularMotion::setRadius(float newRadius) {
    _radius = newRadius;
}
}
