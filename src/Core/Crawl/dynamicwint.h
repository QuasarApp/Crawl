//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef DYNAMICWINT_H
#define DYNAMICWINT_H

#include "wint.h"
namespace CRAWL {

/**
 * @brief The DynamicWint class This implementation dynamicly change wint direction and magnituede per day.
 */
class CRAWL_EXPORT DynamicWint : public Wint
{
    Q_OBJECT
public:
    DynamicWint();

    // IRender interface
public:
    void render(unsigned int tbfMsec) override;

    /**
     * @brief dayLengthSec This method return length of the game day in real secs.
     * @note by default this value is 360 sec
     * @return length of the game day in real secs.
     */
    int dayLengthSec() const;

    /**
     * @brief setDayLengthSec This method sets new value of the day length.
     * @param newDayLongSec This is new value of the day length.
     * @note For get more information see the dayLengthSec method.
     */
    void setDayLengthSec(int newDayLengthSec);

    /**
     * @brief magnitudeVariation This method return curerent value of the magnitude variation.
     * @return curerent value of the magnitude variation.
     */
    unsigned int magnitudeVariation() const;

    /**
     * @brief setMagnitudeVariation This method sets magnitude variation; by default it is 10
     * @param newMagnitudeVariation This is new value of the magitude
     */
    void setMagnitudeVariation(unsigned int newMagnitudeVariation);

    /**
     * @brief baseMagnitude This method return current base magnitude of the wint. The wint will be changed dynamicly one time per day length to the magnitudeVariation
     * @return curretn value of the base magnitude
     */
    unsigned int baseMagnitude() const;

    /**
     * @brief setBaseMagnitude This method sets new value of the base magnitude of the wint.
     * @param newBaseMagnitude  this is new value of the base magnitude of the wint.
     */
    void setBaseMagnitude(unsigned int newBaseMagnitude);

    /**
     * @brief directionChangeMask This method return current value of mask of the direction variation. By default the wint will be changed by x and y axis.
     * @return curertn value of the directionChangeMask
     */
    const QVector3D &directionChangeMask() const;

    /**
     * @brief setDirectionChangeMask This method sets mask of the direction variation. By default the wint will be changed by x and y axis.
     * @param newDirectionChangeMask This is new value of the directionChangeMask
     */
    void setDirectionChangeMask(const QVector3D &newDirectionChangeMask);

private:
    int _dayLengthSec = 360;
    unsigned int _nextWintChange = 0;
    unsigned int _time = 0;

    unsigned int _magnitudeVariation = 50;
    unsigned int _baseMagnitude = 50;

    QVector3D _directionChangeMask = {1, 1, 0};
};

}
#endif // DYNAMICWINT_H
