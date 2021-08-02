//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef FIRE_H
#define FIRE_H

#include "particleeffect.h"

namespace CRAWL {

/**
 * @brief The Fire class This is default implementation of the Fire on game.
 */
class Fire: public ParticleEffect
{
    Q_OBJECT

    /**
     * @brief fireStrength This propertye chenge fire power. By Default it is 10.
    */
    Q_PROPERTY(float fireStrength READ fireStrength WRITE setFireStrength NOTIFY fireStrengthChanged)
public:
    Fire();

    // IWorldItem interface

    /**
     * @brief fireStrength This method return current value of the Fire::fireStrength propertye.
     * @return current value of the Fire::fireStrength propertye.
     */
    float fireStrength() const;

    /**
     * @brief setFireStrength This method sets new value of the Fire::fireStrength propertye.
     * @param newFireStrength This is new value of the Fire::fireStrength prpertye.
     * @warning This method change the emitRate, lifeSpan and velosity propertyes of this objects,
     */
    void setFireStrength(float newFireStrength);

signals:

    /**
     * @brief fireStrengthChanged This signal emited when the Fire::fireStrength propertye is changed.
     */
    void fireStrengthChanged();

protected:
    void onIntersects(const IWorldItem *item);

private:
    float _fireStrength = 0;
};

}
#endif // FIRE_H
