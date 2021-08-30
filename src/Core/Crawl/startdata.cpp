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

StartData::StartData(User *player, IItem* snake) {
    setPlayer(player);
    setSnake(snake);
}


User *StartData::player() const{
    return _player;
}

void StartData::setPlayer(User *newPlayer) {
    _player = newPlayer;
}

IItem *StartData::snake() const {
    return _snake;
}

void StartData::setSnake(IItem *newSnake) {
    _snake = newSnake;
}

}
