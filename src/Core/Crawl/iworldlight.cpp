//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "iworldlight.h"
namespace CRAWL {

IWorldLight::IWorldLight(const QString &name,
                         const QString &viewTempalte,
                         QObject *ptr):
    IWorldItem(name, viewTempalte, ptr) {

}

int IWorldLight::lightForce() const {
    return _lightForce;
}

void IWorldLight::setLightForce(int newLightForce) {
    if (_lightForce == newLightForce)
        return;
    _lightForce = newLightForce;
    emit lightForceChanged();
}

bool IWorldLight::castsShadow() const {
    return _castsShadow;
}

void IWorldLight::setCastsShadow(bool newCastsShadow) {
    if (_castsShadow == newCastsShadow)
        return;
    _castsShadow = newCastsShadow;
    emit castsShadowChanged();
}

float IWorldLight::shadowFactor() const {
    return _shadowFactor;
}

void IWorldLight::setShadowFactor(float newShadowFactor) {
    if (qFuzzyCompare(_shadowFactor, newShadowFactor))
        return;
    _shadowFactor = newShadowFactor;
    emit shadowFactorChanged();
}

float IWorldLight::shadowFilter() const {
    return _shadowFilter;
}

void IWorldLight::setShadowFilter(float newShadowFilter) {
    if (qFuzzyCompare(_shadowFilter, newShadowFilter))
        return;
    _shadowFilter = newShadowFilter;
    emit shadowFilterChanged();
}

float IWorldLight::shadowMapFar() const {
    return _shadowMapFar;
}

void IWorldLight::setShadowMapFar(float newShadowMapFar) {
    if (qFuzzyCompare(_shadowMapFar, newShadowMapFar))
        return;
    _shadowMapFar = newShadowMapFar;
    emit shadowMapFarChanged();
}

float IWorldLight::shadowBias() const {
    return _shadowBias;
}

void IWorldLight::setShadowBias(float newShadowBias) {
    if (qFuzzyCompare(_shadowBias, newShadowBias))
        return;
    _shadowBias = newShadowBias;
    emit shadowBiasChanged();
}

}
