//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "particleeffect.h"
#include "targetdirection.h"
#include "vectordirection.h"
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

const QString &ParticleEffect::particleDelegate() const {
    return _particleDelegate;
}

void ParticleEffect::setParticleDelegate(const QString &newParticleDelegate) {
    if (_particleDelegate == newParticleDelegate)
        return;
    _particleDelegate = newParticleDelegate;
    emit particleDelegateChanged();
}

QObject *ParticleEffect::velocity() const {
    return _velocity;
}

QVector3D ParticleEffect::brust(int count,
                                int duration,
                                const QVector3D &position) const {
    QVector3D result = {0,0,0};

    if (!viewObject()) {
        QuasarAppUtils::Params::log("Failed to brust particles because the viewObject is empty.");
        return result;
    }

    QMetaObject::invokeMethod(viewObject(),
                              "brust",
                              Qt::DirectConnection,
                              Q_RETURN_ARG(QVector3D, result),
                              Q_ARG(int, count),
                              Q_ARG(int, duration),
                              Q_ARG(QVector3D, position));

    return result;
}

QVector3D ParticleEffect::brust(int count, int duration) const {

    QVector3D result = {0,0,0};

    if (!viewObject()) {
        QuasarAppUtils::Params::log("Failed to brust particles because the viewObject is empty.");
        return result;
    }

    QMetaObject::invokeMethod(viewObject(),
                              "brust",
                              Qt::DirectConnection,
                              Q_RETURN_ARG(QVector3D, result),
                              Q_ARG(int, count),
                              Q_ARG(int, duration));

    return result;
}

QVector3D ParticleEffect::brust(int count) const {

    QVector3D result = {0,0,0};

    if (!viewObject()) {
        QuasarAppUtils::Params::log("Failed to brust particles because the viewObject is empty.");
        return result;
    }

    QMetaObject::invokeMethod(viewObject(),
                              "brust",
                              Qt::DirectConnection,
                              Q_RETURN_ARG(QVector3D, result),
                              Q_ARG(int, count));

    return result;
}

void ParticleEffect::setVelocity(QObject *newVelocity) {
    if (_velocity == newVelocity)
        return;
    _velocity = newVelocity;
    emit velocityChanged();
}

const QVector3D &ParticleEffect::particleRotation() const {
    return _particleRotation;
}

void ParticleEffect::setParticleRotation(const QVector3D &newParticleRotation) {
    if (_particleRotation == newParticleRotation)
        return;
    _particleRotation = newParticleRotation;
    emit particleRotationChanged();
}

const QString &ParticleEffect::particleShape() const {
    return _particleShape;
}

void ParticleEffect::setParticleShape(const QString &newParticleShape) {
    if (_particleShape == newParticleShape)
        return;
    _particleShape = newParticleShape;
    emit particleShapeChanged();
}

void ParticleEffect::useDirectionVelosity(
        const QVector3D& velosityDirection,
        const QVector3D& velosityDirectionValatility) {

    if (_velocity) {
        _velocity->deleteLater();
    }

    setVelocity(new VectorDirection(velosityDirection, velosityDirectionValatility));
}

void ParticleEffect::useTargetVelosity(
        float velosityMagnitude,
        float velosityMagnitudeVariation,
        bool velosityNormalized,
        const QVector3D& velosityTargetPosition,
        const QVector3D& velosityTargetPositionVariation) {

    if (_velocity) {
        _velocity->deleteLater();
    }

    setVelocity(new TargetDirection(velosityMagnitude,
                                    velosityMagnitudeVariation,
                                    velosityNormalized,
                                    velosityTargetPosition,
                                    velosityTargetPositionVariation));
};

}
