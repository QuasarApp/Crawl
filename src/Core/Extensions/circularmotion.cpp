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
        renderPosition(_this, tbfMsec);
        renderRatation(_this, tbfMsec);
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

double CircularMotion::anglePosition() const {
    return _angle;
}

void CircularMotion::setAnglePosition(double newAngle) {
    _angle = newAngle;
}

void CircularMotion::renderRatation(GuiObject *object,
                                    unsigned int ) {
    object->setRatation(QQuaternion::rotationTo({1.0f, 0.0, 0.0}, *_center) * staticRotation());
}

void CircularMotion::renderPosition(GuiObject *object,
                                    unsigned int tbfMsec) {

    if (!_center)
        return;

    double motionCoef = 360 / (2 * M_PI * radius());
    _angle += motionCoef * angularVelocity() * (tbfMsec / 1000.f);
    auto normal = (QQuaternion::fromAxisAndAngle(_axis, _angle) * QVector3D{0,0,1}).normalized();

    object->setposition(*_center + normal * radius());

}
}
