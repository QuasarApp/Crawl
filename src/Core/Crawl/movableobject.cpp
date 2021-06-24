#include "movableobject.h"
#include <QDebug>

MovableObject::MovableObject(const QString &name,
                             const QString &viewTempalte,
                             QObject *ptr):
    IWorldItem(name, viewTempalte, ptr) {

}

void MovableObject::render(unsigned int tbfMsec) {

    // get object center position
    QVector3D currentPosition = position();

    // move object to vector
    currentPosition += (_currentMovableVector * (tbfMsec / 1000.0));
    setposition(currentPosition);

    // calc temp vector betvin user moveble vector and real moveble vector
    QVector3D tempVector = _movableVector - _currentMovableVector ;

    // calc change on this iteration for new moveble vector
    float delta = std::min(_angularVelocity * (tbfMsec / 1000.0), static_cast<double>(tempVector.length()));

    // resize temp vector for calc changes of the movableVector
    tempVector = tempVector.normalized() * delta;

    // recalc new currentMovable vector (applay changes)
    _currentMovableVector += tempVector;

    float newMovableVectorLength = std::max(_movableVector.length() - (_breakingForce * (tbfMsec / 1000.0)), 0.0);

    // update movable vector
    _movableVector = _movableVector.normalized() * newMovableVectorLength;

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
