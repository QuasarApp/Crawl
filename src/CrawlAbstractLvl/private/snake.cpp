//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "snake.h"

void Snake::onIntersects(const IWorldItem *item) {
    Q_UNUSED(item);
}

void Snake::onTap() {

}

Snake::Snake(): IPlayer("Snake") {

}

void Snake::setControl(const IControl *control) {
    Q_UNUSED(control);
}
