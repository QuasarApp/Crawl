//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "particleeffect.h"
namespace CRAWL {


ParticleEffect::ParticleEffect(const QString &name,
                               const QString &viewTempalte,
                               QObject *ptr):
    IWorldItem(name, viewTempalte, ptr) {

}

bool ParticleEffect::enabled() const {
    return _enabled;
}

void ParticleEffect::setEnabled(bool newEnabled) {
    if (_enabled == newEnabled)
        return;
    _enabled = newEnabled;
    emit enabledChanged();
}

float ParticleEffect::emitRate() const {
    return _emitRate;
}

void ParticleEffect::setEmitRate(float newEmitRate) {
    if (qFuzzyCompare(_emitRate, newEmitRate))
        return;
    _emitRate = newEmitRate;
    emit emitRateChanged();
}

float ParticleEffect::depthBias() const {
    return _depthBias;
}

void ParticleEffect::setDepthBias(float newDepthBias) {
    if (qFuzzyCompare(_depthBias, newDepthBias))
        return;
    _depthBias = newDepthBias;
    emit depthBiasChanged();
}

int ParticleEffect::lifeSpan() const {
    return _lifeSpan;
}

void ParticleEffect::setLifeSpan(int newLifeSpan) {
    if (_lifeSpan == newLifeSpan)
        return;
    _lifeSpan = newLifeSpan;
    emit lifeSpanChanged();
}

int ParticleEffect::lifeSpanVariation() const {
    return _lifeSpanVariation;
}

void ParticleEffect::setLifeSpanVariation(int newLifeSpanVariation) {
    if (_lifeSpanVariation == newLifeSpanVariation)
        return;
    _lifeSpanVariation = newLifeSpanVariation;
    emit lifeSpanVariationChanged();
}

float ParticleEffect::particleEndScale() const {
    return _particleEndScale;
}

void ParticleEffect::setParticleEndScale(float newParticleEndScale) {
    if (qFuzzyCompare(_particleEndScale, newParticleEndScale))
        return;
    _particleEndScale = newParticleEndScale;
    emit particleEndScaleChanged();
}

const QVector3D &ParticleEffect::particleRotationVariation() const {
    return _particleRotationVariation;
}

void ParticleEffect::setParticleRotationVariation(const QVector3D &newParticleRotationVariation) {
    if (_particleRotationVariation == newParticleRotationVariation)
        return;
    _particleRotationVariation = newParticleRotationVariation;
    emit particleRotationVariationChanged();
}

const QVector3D &ParticleEffect::particleRotationVelocity() const {
    return _particleRotationVelocity;
}

void ParticleEffect::setParticleRotationVelocity(const QVector3D &newParticleRotationVelocity) {
    if (_particleRotationVelocity == newParticleRotationVelocity)
        return;
    _particleRotationVelocity = newParticleRotationVelocity;
    emit particleRotationVelocityChanged();
}

const QVector3D &ParticleEffect::particleRotationVelocityVariation() const {
    return _particleRotationVelocityVariation;
}

void ParticleEffect::setParticleRotationVelocityVariation(const QVector3D &newParticleRotationVelocityVariation) {
    if (_particleRotationVelocityVariation == newParticleRotationVelocityVariation)
        return;
    _particleRotationVelocityVariation = newParticleRotationVelocityVariation;
    emit particleRotationVelocityVariationChanged();
}

float ParticleEffect::particleScale() const {
    return _particleScale;
}

void ParticleEffect::setParticleScale(float newParticleScale) {
    if (qFuzzyCompare(_particleScale, newParticleScale))
        return;
    _particleScale = newParticleScale;
    emit particleScaleChanged();
}

float ParticleEffect::particleScaleVariation() const {
    return _particleScaleVariation;
}

void ParticleEffect::setParticleScaleVariation(float newParticleScaleVariation) {
    if (qFuzzyCompare(_particleScaleVariation, newParticleScaleVariation))
        return;
    _particleScaleVariation = newParticleScaleVariation;
    emit particleScaleVariationChanged();
}

const QVector3D &ParticleEffect::velosityDirection() const {
    return _velosityDirection;
}

void ParticleEffect::setVelosityDirection(const QVector3D &newVelosityDirection) {
    if (_velosityDirection == newVelosityDirection)
        return;
    _velosityDirection = newVelosityDirection;
    emit velosityDirectionChanged();
}

const QVector3D &ParticleEffect::velosityDirectionValatility() const {
    return _velosityDirectionValatility;
}

void ParticleEffect::setVelosityDirectionValatility(const QVector3D &newVelosityDirectionValatility) {
    if (_velosityDirectionValatility == newVelosityDirectionValatility)
        return;
    _velosityDirectionValatility = newVelosityDirectionValatility;
    emit velosityDirectionValatilityChanged();
}

float ParticleEffect::velosityMagnitude() const {
    return _velosityMagnitude;
}

void ParticleEffect::setVelosityMagnitude(float newVelosityMagnitude) {
    if (qFuzzyCompare(_velosityMagnitude, newVelosityMagnitude))
        return;
    _velosityMagnitude = newVelosityMagnitude;
    emit velosityMagnitudeChanged();
}

float ParticleEffect::velosityMagnitudeVariation() const {
    return _velosityMagnitudeVariation;
}

void ParticleEffect::setVelosityMagnitudeVariation(float newVelosityMagnitudeVariation) {
    if (qFuzzyCompare(_velosityMagnitudeVariation, newVelosityMagnitudeVariation))
        return;
    _velosityMagnitudeVariation = newVelosityMagnitudeVariation;
    emit velosityMagnitudeVariationChanged();
}

bool ParticleEffect::velosityNormalized() const {
    return _velosityNormalized;
}

void ParticleEffect::setVelosityNormalized(bool newVelosityNormalized) {
    if (_velosityNormalized == newVelosityNormalized)
        return;
    _velosityNormalized = newVelosityNormalized;
    emit velosityNormalizedChanged();
}

const QVector3D &ParticleEffect::velosityTargetPosition() const {
    return _velosityTargetPosition;
}

void ParticleEffect::setVelosityTargetPosition(const QVector3D &newVelosityTargetPosition) {
    if (_velosityTargetPosition == newVelosityTargetPosition)
        return;
    _velosityTargetPosition = newVelosityTargetPosition;
    emit velosityTargetPositionChanged();
}

const QVector3D &ParticleEffect::velosityTargetPositionVariation() const {
    return _velosityTargetPositionVariation;
}

void ParticleEffect::setVelosityTargetPositionVariation(const QVector3D &newVelosityTargetPositionVariation) {
    if (_velosityTargetPositionVariation == newVelosityTargetPositionVariation)
        return;
    _velosityTargetPositionVariation = newVelosityTargetPositionVariation;
    emit velosityTargetPositionVariationChanged();
}

const QString &ParticleEffect::particleDelegate() const {
    return _particleDelegate;
}

void ParticleEffect::setParticleDelegate(const QString &newParticleDelegate) {
    if (_particleDelegate == newParticleDelegate)
        return;
    _particleDelegate = newParticleDelegate;
    emit particleDelegateChanged();
}

}
