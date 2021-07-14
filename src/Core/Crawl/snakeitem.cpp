//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "snake.h"
#include "snakeitem.h"

namespace CRAWL {


SnakeItem::SnakeItem(const QString &name, const QString &viewTempalte, QObject *ptr):
    SingleClasterWorldItem(name, viewTempalte, ptr) {
    setAngularVelocity(-1);

}

void SnakeItem::setPrev(const IWorldItem * newPrev) {
    _prevObject = newPrev;
}

void SnakeItem::render(unsigned int tbfMsec) {

    if (!_prevObject) {
        return;
    }

    auto ratationVector = (_prevObject->position() - position());

    if (auto claster = static_cast<Snake*>(parentClaster())) {
        float ratationLength = ratationVector.length();

        if (ratationLength > lengthBetwinItems() * 10) {
            setposition(_prevObject->position());
        } else if (ratationLength > lengthBetwinItems()) {
            setMovableVector(ratationVector.normalized() * claster->currentMovableVector().length());
        }
    }

    MovableObject::render(tbfMsec);
}

const IWorldItem * SnakeItem::prev() const {
    return _prevObject;
}

float SnakeItem::lengthBetwinItems() const {
    return _lengthBetwinItems;
}

void SnakeItem::setLengthBetwinItems(float newLengthBetwinItems) {
    _lengthBetwinItems = newLengthBetwinItems;
}
}
