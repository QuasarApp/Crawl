//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "wint.h"

namespace CRAWL {

Wint::Wint(): Affector(AUTO_CLASS_NAME, "qrc:/CrawlModule/particles/Wint.qml") {
}

float Wint::magnitude() const {
    return _magnitude;
}

void Wint::setMagnitude(float newMagnitude) {
    if (qFuzzyCompare(_magnitude, newMagnitude))
        return;
    _magnitude = newMagnitude;
    emit magnitudeChanged();
}

const QVector3D &Wint::direction() const {
    return _direction;
}

void Wint::setDirection(const QVector3D &newDirection) {
    if (_direction == newDirection)
        return;
    _direction = newDirection;
    emit directionChanged();
}

}
