//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "snake.h"
#include "snakeitem.h"

SnakeItem::SnakeItem(const QString itemName): SingleClasterWorldItem(itemName) {

}

void SnakeItem::setPrev(int newPrev) {
    _prev = newPrev;
}

void SnakeItem::render(unsigned int tbfMsec) {
    auto prev = getItem(_prev);
    auto ratationVector = (prev->position() - position());

    if (auto claster = static_cast<Snake*>(parentClaster())) {
        if (ratationVector.length() < claster->lengthBetwinItems()) {
            setMovableVector({0,0,0});
        } else {
            setMovableVector(ratationVector *= claster->speed());
        }
    }

    MovableObject::render(tbfMsec);
}

int SnakeItem::prev() const {
    return _prev;
}
