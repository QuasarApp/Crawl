//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "player.h"
#include <user.h>

namespace CRAWL {

Player::Player() {

}

void Player::addXp(int newXp) {
    if (_userData)
        _userData->setXp(_userData->getXp() + newXp);
}

void Player::addMoney(int money) {
    if (_userData)
        _userData->setMoney(_userData->getMoney() + money);
}

User *Player::userData() const {
    return _userData;
}

void Player::setUserData(User *newUserData) {
    _userData = newUserData;
}
}
