//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "targetdirection.h"
namespace CRAWL {

TargetDirection::TargetDirection(float velosityMagnitude,
                                 float velosityMagnitudeVariation,
                                 bool velosityNormalized,
                                 const QVector3D &velosityTargetPosition,
                                 const QVector3D &velosityTargetPositionVariation,
                                 QObject *parent):
    ViewTemaplateModel("qrc:/CrawlModule/particles/CrawlTargetDirection.qml", parent)
{
    setVelosityMagnitude(velosityMagnitude);
    setVelosityMagnitudeVariation(velosityMagnitudeVariation);
    setVelosityNormalized(velosityNormalized);
    setVelosityTargetPosition(velosityTargetPosition);
    setVelosityTargetPositionVariation(velosityTargetPositionVariation);
}

float TargetDirection::velosityMagnitude() const {
    return _velosityMagnitude;
}

void TargetDirection::setVelosityMagnitude(float newVelosityMagnitude) {
    if (qFuzzyCompare(_velosityMagnitude, newVelosityMagnitude))
        return;
    _velosityMagnitude = newVelosityMagnitude;
    emit velosityMagnitudeChanged();
}

float TargetDirection::velosityMagnitudeVariation() const {
    return _velosityMagnitudeVariation;
}

void TargetDirection::setVelosityMagnitudeVariation(float newVelosityMagnitudeVariation) {
    if (qFuzzyCompare(_velosityMagnitudeVariation, newVelosityMagnitudeVariation))
        return;
    _velosityMagnitudeVariation = newVelosityMagnitudeVariation;
    emit velosityMagnitudeVariationChanged();
}

bool TargetDirection::velosityNormalized() const {
    return _velosityNormalized;
}

void TargetDirection::setVelosityNormalized(bool newVelosityNormalized) {
    if (_velosityNormalized == newVelosityNormalized)
        return;
    _velosityNormalized = newVelosityNormalized;
    emit velosityNormalizedChanged();
}

const QVector3D &TargetDirection::velosityTargetPosition() const {
    return _velosityTargetPosition;
}

void TargetDirection::setVelosityTargetPosition(const QVector3D &newVelosityTargetPosition) {
    if (_velosityTargetPosition == newVelosityTargetPosition)
        return;
    _velosityTargetPosition = newVelosityTargetPosition;
    emit velosityTargetPositionChanged();
}

const QVector3D &TargetDirection::velosityTargetPositionVariation() const {
    return _velosityTargetPositionVariation;
}

void TargetDirection::setVelosityTargetPositionVariation(const QVector3D &newVelosityTargetPositionVariation) {
    if (_velosityTargetPositionVariation == newVelosityTargetPositionVariation)
        return;
    _velosityTargetPositionVariation = newVelosityTargetPositionVariation;
    emit velosityTargetPositionVariationChanged();
}
}
