//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "movableobject.h"
#include <math.h>
#include <Crawl/guiobject.h>

namespace CRAWL {


MovableObject::MovableObject() {

}

void MovableObject::render(unsigned int tbfMsec) {

    if (auto _this = checkminimumRequariedType<GuiObject>()) {
        renderPosition(_this, tbfMsec);
        renderRatation(_this, tbfMsec);
    }
}

const QVector3D &MovableObject::movableVector() const  {
    return _movableVector;
}

void MovableObject::setMovableVector(const QVector3D &newMovableVector) {
    _movableVector = newMovableVector;
}

float MovableObject::angularVelocity() const {
    return _angularVelocity;
}

void MovableObject::setAngularVelocity(float newAngularVelocity) {
    _angularVelocity = newAngularVelocity;
}

float MovableObject::breakingForce() const {
    return _breakingForce;
}

void MovableObject::setBreakingForce(float newBreakingForce) {
    _breakingForce = newBreakingForce;
}

void MovableObject::renderRatation(GuiObject *object, unsigned int) {
    if (_currentMovableVector.length() > 0) {
        object->setRatation(QQuaternion::rotationTo({1.0f, 0.0, 0.0}, _currentMovableVector));
    }
}

void MovableObject::renderPosition(GuiObject *object, unsigned int tbfMsec) {
    // get object center position
    QVector3D currentPosition = object->position();

    // move object to vector
    currentPosition += (_currentMovableVector * (tbfMsec / 1000.0));
    object->setposition(currentPosition);

    // calc temp vector betvin user moveble vector and real moveble vector
    QVector3D tempVector = _movableVector - _currentMovableVector ;

    // calc change on this iteration for new moveble vector
    float delta = 0.0;
    if (_angularVelocity <= 0) {
        delta = tempVector.length();
    } else {
        delta = std::min(_angularVelocity * (tbfMsec / 1000.0), static_cast<double>(tempVector.length()));
    }

    // resize temp vector for calc changes of the movableVector
    tempVector = tempVector.normalized() * delta;

    // recalc new currentMovable vector (applay changes)
    _currentMovableVector += tempVector;

    float newMovableVectorLength = std::max(_movableVector.length() - (_breakingForce * (tbfMsec / 1000.0)), 0.0);

    // update movable vector
    _movableVector = _movableVector.normalized() * newMovableVectorLength;

}

const QVector3D &MovableObject::currentMovableVector() const {
    return _currentMovableVector;
}

}
