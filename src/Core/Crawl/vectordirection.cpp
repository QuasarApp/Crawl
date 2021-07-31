//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "vectordirection.h"

namespace CRAWL {

VectorDirection::VectorDirection(const QVector3D &direction,
                                 const QVector3D &directionValatility,
                                 QObject *parent):
    ViewTemaplateModel("qrc:/CrawlModule/particles/CrawlVectorDirection.qml", parent) {

    setVelosityDirection(direction);
    setVelosityDirectionValatility(directionValatility);
}

const QVector3D &VectorDirection::velosityDirection() const {
    return _velosityDirection;
}

void VectorDirection::setVelosityDirection(const QVector3D &newVelosityDirection) {
    if (_velosityDirection == newVelosityDirection)
        return;
    _velosityDirection = newVelosityDirection;
    emit velosityDirectionChanged();
}

const QVector3D &VectorDirection::velosityDirectionValatility() const {
    return _velosityDirectionValatility;
}

void VectorDirection::setVelosityDirectionValatility(const QVector3D &newVelosityDirectionValatility) {
    if (_velosityDirectionValatility == newVelosityDirectionValatility)
        return;
    _velosityDirectionValatility = newVelosityDirectionValatility;
    emit velosityDirectionValatilityChanged();
}

}
