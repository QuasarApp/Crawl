//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "iitem.h"
#include "ilevel.h"
#include "ipreviewscaneworld.h"

namespace CRAWL {

ILevel::~ILevel() {
    delete _world;
    delete _previewScane;

    for (auto i : qAsConst(_items)) {
        delete i;
    }

    _items.clear();
}

IWorld *ILevel::world() const {
    return _world;
}

IPreviewScaneWorld *ILevel::previewScane() const {
    return _previewScane;
}

void ILevel::reset() {
    _world->reset();
    _previewScane->reset();
}

const QMultiHash<int, IItem *> &ILevel::availableItems() const {
    return _items;
}

void ILevel::setWorld(IWorld *newWorld) {
    _world = newWorld;
}

void ILevel::setPreviewScane(IPreviewScaneWorld *newPreviewScane) {
    _previewScane = newPreviewScane;
}

void ILevel::addItem(IItem *item) {
    _items[item->itemId()] = item;
}

}
