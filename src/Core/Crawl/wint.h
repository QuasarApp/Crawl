//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef WINT_H
#define WINT_H

#include "affector.h"
#include "Extensions/rotationaroundaxis.h"

namespace CRAWL {

/**
 * @brief The Wint class This is example of the using Affector class.
 * implementation of the wint.
 */
class CRAWL_EXPORT Wint: public Affector
{
    Q_OBJECT


    /**
     * @brief direction This property defines the direction the gravity will affect toward. Values will be automatically normalized to a unit vector.
    */
    Q_PROPERTY(QVector3D direction READ direction WRITE setDirection NOTIFY directionChanged)

    /**
     * @brief magnitude This property defines the magnitude in position change per second. Negative magnitude accelerates the opposite way from the direction.
The default value is 100.0.
     */
    Q_PROPERTY(float magnitude READ magnitude WRITE setMagnitude NOTIFY magnitudeChanged)

public:
    Wint();

    // IWorldItem interface
    /**
     * @brief direction This method return current direction of the wint.
     * @return  direction of the wint.
     */
    const QVector3D &direction() const;

    /**
     * @brief setDirection This method sets new direction of the wint.
     * @param newDirection new value of the direction of the wint.
     */
    void setDirection(const QVector3D &newDirection);

    /**
     * @brief magnitude This property defines the magnitude in position change per second. Negative magnitude accelerates the opposite way from the direction.
The default value is 10.0.
     * @return current value of the magnitude.
     */
    float magnitude() const;

    /**
     * @brief setMagnitude This method sets new vlaue of the magnitucde of this object.
     * @param newMagnitude Tis is new value of the magnitude property
     */
    void setMagnitude(float newMagnitude);

signals:
    void directionChanged();
    void magnitudeChanged();

private:

    QVector3D _direction = {1, 0, 0};
    float _magnitude = 10;
};
}
#endif // WINT_H
