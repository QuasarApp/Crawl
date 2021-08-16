//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "startdata.h"

namespace CRAWL {

StartData::StartData() {

}

StartData::StartData(User *player, int snake) {
    setPlayer(player);
    setSnakeType(snake);
}


User *StartData::player() const{
    return _player;
}

void StartData::setPlayer(User *newPlayer) {
    _player = newPlayer;
}

int StartData::snakeType() const {
    return _snakeType;
}

void StartData::setSnakeType(int newSnake) {
    _snakeType = newSnake;
}

const QSet<int> &StartData::snakePerks() const {
    return _snakePerks;
}

void StartData::setSnakePerks(const QSet<int> &newSnakePerks) {
    _snakePerks = newSnakePerks;
}

}
