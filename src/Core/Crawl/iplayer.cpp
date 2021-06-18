//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "iplayer.h"

IPlayer::IPlayer(const QString &name,
                 const QString &viewTempalte,
                 QObject *ptr):
    IWorldItem(name, viewTempalte, ptr) {

}

GameResult IPlayer::getCurrentStatus() const {
    return {_currentPoints, static_cast<int>(position().distanceToPoint({0,0,0}))};
}

bool IPlayer::isDead() const {
    return _fDead;
}

void IPlayer::reward(int value) {
    _currentPoints += value;
}

float IPlayer::speedUp(float increment) {
    setSpeed(_speed + increment);
    return _speed;
}

float IPlayer::setSpeedDown(float decrement) {
    setSpeed(_speed - decrement);
    return _speed;
}

void IPlayer::fine(int value) {
    _currentPoints -= value;
}

float IPlayer::speed() const {
    return _speed;
}

void IPlayer::setSpeed(float newSpead) {
    _speed = newSpead;

    if (_speed < 0) {
        _speed = 0;
    }
}

void IPlayer::kill() {
    _fDead = true;
}
