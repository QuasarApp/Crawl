//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "gamesession.h"
namespace CRAWL {

GameSession::GameSession() {

}

int GameSession::xp() const {
    return _xp;
}

void GameSession::setXp(int newXp) {
    _xp = newXp;
}

int GameSession::money() const {
    return _money;
}

void GameSession::setMoney(int newMoney) {
    _money = newMoney;
}

}
