//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef DAYLIGHT_H
#define DAYLIGHT_H

#include "iworldlight.h"

namespace CRAWL {

/**
 * @brief The DayLight class
 */
class CRAWL_EXPORT DayLight final: public IWorldLight
{
    Q_OBJECT
    Q_PROPERTY(QString moonColor READ moonColor NOTIFY moonColorChanged)
    Q_PROPERTY(int moonLightForce READ moonLightForce NOTIFY moonLightForceChanged)

public:
    DayLight();
    ~DayLight() override;

    void render(unsigned int tbfMsec) override;

    // IWorldItem interface

    /**
     * @brief getDayLengthSec This method return current value of the day length. by default one day = 60 sec.
     * @return current value of the day length
     */
    int getDayLengthSec() const;

    /**
     * @brief setDayLengthSec This method sets new value of the day length property.
     * @param newDayLengthSec This is new value of the day length property.
     */
    void setDayLengthSec(int newDayLengthSec);

    /**
     * @brief resetTime This method reset current day time to 0.
     */
    void resetTime();

    /**
     * @brief curerntTime This method return current time of the day.
     * @return current time of the day.
     */
    const QTime &curerntTime() const;

    /**
     * @brief moonColor This method return current color of the moon object.
     * @return current color of the moon object.
     */
    const QString &moonColor() const;

    /**
     * @brief setMoonColor This method sets new value for the mool color.
     * @param newMoonColor This is new value of the moonColor property
     */
    void setMoonColor(const QString &newMoonColor);

    /**
     * @brief sunColor This method is wrapper of the color method.
     * @return return current sun color.
     */
    const QString &sunColor() const;

    /**
     * @brief setSunColor This method is wrapper of the setColor method.
     * @param newSunColor sets new value of the color property
     */
    void setSunColor(const QString &newSunColor);

    /**
     * @brief moonLightForce This method return current value of the light force for moon
     * @return current value of the light force for moon
     */
    int moonLightForce() const;

    /**
     * @brief setMoonLightForce This method sets new value of the moon light force.
     * @param newMoonLightForce this is new value of the moon light force.
     */
    void setMoonLightForce(int newMoonLightForce);

    /**
     * @brief sunLightForce This method is wrapper of the lightForce method
     * @return current sun light force.
     */
    int sunLightForce() const;

    /**
     * @brief setSunLightForce This method is wrapper of the setLightForce method.
     * @param newSunLightForce this is new value of the sun light force
     */
    void setSunLightForce(int newSunLightForce);

signals:

    /**
     * @brief moonColorChanged This signal emits when color of the moon has been changed.
     */
    void moonColorChanged();

    /**
     * @brief moonColorChanged This signal emits when light force of the moon has been changed.
     */
    void moonLightForceChanged();

protected:
    void onIntersects(const IWorldItem *) override;

private:
    int dayLengthSec = 60;
    QTime *_curerntTime = nullptr;
    QTime *_zeroTime = nullptr;

    QString _moonColor;
    int _moonLightForce;
};
}
#endif // DAYLIGHT_H
