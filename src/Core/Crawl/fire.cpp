//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "fire.h"
#include "vectordirection.h"

namespace CRAWL {

Fire::Fire(): ParticleEffect(AUTO_CLASS_NAME, "qrc:/CrawlModule/particles/Fire.qml") {

    useDirectionVelosity({0, 0 , 10}, {10, 10, 0});
    setParticleScale(1);
    setParticleEndScale(3);
    setParticleScaleVariation(3);

    setLifeSpanVariation(500);
    setColor("#ffaf2c");
    setSize({1, 1, 1});
    setposition({0,0,10});
    setEnabled(true);

    setParticleDelegate("qrc:/CrawlModule/particles/FireParticel.qml");

    setFireStrength(100);
}

void CRAWL::Fire::onIntersects(const IWorldItem *) {

}

float Fire::fireStrength() const {
    return _fireStrength;
}

void Fire::setFireStrength(float newFireStrength) {
    if (qFuzzyCompare(_fireStrength, newFireStrength))
        return;

    _fireStrength = newFireStrength;

    setEmitRate(10 + _fireStrength);
    setLifeSpan(1000 + _fireStrength);

    auto vel = static_cast<VectorDirection*>(velocity());
    vel->setVelosityDirection({0, 0 , _fireStrength / 4});
    vel->setVelosityDirectionValatility({10, 10, 0});

    emit fireStrengthChanged();
}

}
