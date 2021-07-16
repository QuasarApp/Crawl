//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "daylight.h"

#include <QTime>

namespace CRAWL {

DayLight::DayLight():
    IWorldLight(AUTO_CLASS_NAME, "qrc:/CrawlModule/DayLight.qml") {

    _curerntTime = new QTime(0,0,0);
    _zeroTime = new QTime(0,0,0);
    setposition({0, 0, 0});
    setColor("#fff8e7");
    setMoonColor("#fff8e7");
    setSunLightForce(200);
    setMoonLightForce(20);


}

DayLight::~DayLight() {
    delete _curerntTime;
    delete _zeroTime;
}

void DayLight::render(unsigned int tbfMsec) {
#define ONE_DAY (24 * 60 * 60)
#define DELTA (ONE_DAY /  dayLengthSec)
#define TIME (tbfMsec / 1000.f)

    *_curerntTime = _curerntTime->addSecs(DELTA * TIME);

#define ANGLE _zeroTime->secsTo(*_curerntTime) / static_cast<float>(ONE_DAY)

//    setRatation(QQuaternion::fromEulerAngles({ANGLE, 0, 0}));
}

void DayLight::onIntersects(const IWorldItem *) {

}

int DayLight::sunLightForce() const {
    return lightForce();
}

void DayLight::setSunLightForce(int newSunLightForce) {
    setLightForce(newSunLightForce);
}

int DayLight::moonLightForce() const {
    return _moonLightForce;
}

void DayLight::setMoonLightForce(int newMoonLightForce)
{
    if (_moonLightForce == newMoonLightForce)
        return;
    _moonLightForce = newMoonLightForce;
    emit moonLightForceChanged();
}

const QString &DayLight::sunColor() const {
    return color();
}

void DayLight::setSunColor(const QString &newSunColor) {
    setColor(newSunColor);
}

const QString &DayLight::moonColor() const {
    return _moonColor;
}

void DayLight::setMoonColor(const QString &newMoonColor) {
    if (_moonColor == newMoonColor)
        return;
    _moonColor = newMoonColor;
    emit moonColorChanged();
}

const QTime &DayLight::curerntTime() const {
    return *_curerntTime;
}

int DayLight::getDayLengthSec() const {
    return dayLengthSec;
}

void DayLight::setDayLengthSec(int newDayLengthSec) {
    dayLengthSec = newDayLengthSec;
}

void DayLight::resetTime() {
    _curerntTime->setHMS(0,0,0,0);
}
}
