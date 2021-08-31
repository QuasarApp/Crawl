//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "availablesnakesmodel.h"

namespace CRAWL {

AvailableSnakesModel::AvailableSnakesModel() {

}

int AvailableSnakesModel::getCurrentSnake() const {
    return _currentSnake;
}

void AvailableSnakesModel::setCurrentSnake(int newCurrentSnake) {
    if (_currentSnake == newCurrentSnake)
        return;

    _currentSnake = newCurrentSnake;
    emit currentSnakeChanged();
}

}
