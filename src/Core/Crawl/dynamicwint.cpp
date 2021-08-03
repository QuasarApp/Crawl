//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "dynamicwint.h"

namespace CRAWL {

DynamicWint::DynamicWint() {

}

void DynamicWint::render(unsigned int tbfMsec) {
    _time += tbfMsec;

    if (_time > _nextWintChange) {
        setMagnitude(_baseMagnitude + (rand() % _magnitudeVariation) - _magnitudeVariation / 2 );
        setDirection(QVector3D{static_cast<float>(rand()) - rand(), static_cast<float>(rand()) - rand(), static_cast<float>(rand()) - rand()} * _directionChangeMask);

        _nextWintChange += ((rand() % 100) / 100.0f) *  dayLengthSec() * 1000;
    }
}

int DynamicWint::dayLengthSec() const {
    return _dayLengthSec;
}

void DynamicWint::setDayLengthSec(int newDayLengthSec) {
    _dayLengthSec = newDayLengthSec;
}

unsigned int DynamicWint::magnitudeVariation() const {
    return _magnitudeVariation;
}

void DynamicWint::setMagnitudeVariation(unsigned int newMagnitudeVariation) {
    _magnitudeVariation = newMagnitudeVariation;
}

unsigned int DynamicWint::baseMagnitude() const {
    return _baseMagnitude;
}

void DynamicWint::setBaseMagnitude(unsigned int newBaseMagnitude) {
    _baseMagnitude = newBaseMagnitude;
}

const QVector3D &DynamicWint::directionChangeMask() const {
    return _directionChangeMask;
}

void DynamicWint::setDirectionChangeMask(const QVector3D &newDirectionChangeMask) {
    _directionChangeMask = newDirectionChangeMask;
}

}
