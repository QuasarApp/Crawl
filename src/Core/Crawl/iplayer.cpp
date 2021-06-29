//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "defaultcontrol.h"
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

void IPlayer::fine(int value) {
    _currentPoints -= value;
}

void IPlayer::render(unsigned int tbfMsec) {
    MovableObject::render(tbfMsec);
}

void IPlayer::setControl(const IControl *control) {


    if (auto oldControl = dynamic_cast<const DefaultControl*>(_currentControl)) {
        disconnect(oldControl, &DefaultControl::userTap, this, &IPlayer::onTap);
    }

    auto defaultControl = dynamic_cast<const DefaultControl*>(control);
    _currentControl = defaultControl;

    if (_currentControl) {
        connect(defaultControl, &DefaultControl::userTap, this, &IPlayer::onTap);
    }
}

void IPlayer::kill() {
    _fDead = true;
}
