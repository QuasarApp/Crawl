//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "clasteritem.h"
#include "snake.h"
#include "snakeitem.h"
#include <QQuaternion>
#include <quasarapp.h>

Snake::Snake(const QString &name, const QString &viewTempalte, QObject *ptr):
    IPlayer (name, viewTempalte, ptr) {

}

void Snake::render(unsigned int tbfMsec) {
    IPlayer::render(tbfMsec);
}

void Snake::add(ClasterItem *object) {
    if (auto snakeItem = dynamic_cast<SnakeItem*>(object)) {
        snakeItem->setPrev(_lastSnakeItem->guiId());
        _lastSnakeItem = static_cast<IWorldItem*>(snakeItem);

        Claster::add(object);
        return ;
    }

    QuasarAppUtils::Params::log("Failed to add item to Snake."
                                " You need to use the SnakeItem child class as a argument",
                                QuasarAppUtils::Error);
}

void Snake::remove(ClasterItem *object) {

    if (_lastSnakeItem == object) {
        _lastSnakeItem = getItem(static_cast<const SnakeItem*>(_lastSnakeItem)->prev());
    }

    return Claster::remove(object);
}

void Snake::remove(int id) {
    if (_lastSnakeItem->guiId() == id) {
        _lastSnakeItem = getItem(static_cast<const SnakeItem*>(_lastSnakeItem)->prev());
    }

    return Claster::remove(id);
}

void Snake::onTap() {

}

float Snake::lengthBetwinItems() const{
    return _lengthBetwinItems;
}

void Snake::setLengthBetwinItems(float newLengthBetwinItems) {
    _lengthBetwinItems = newLengthBetwinItems;
}
