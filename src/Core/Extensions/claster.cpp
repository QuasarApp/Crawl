//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "claster.h"
#include "Crawl/singleclasterworlditem.h"

Claster::Claster() {}

Claster::~Claster() {
    for (auto child : qAsConst(_objects)) {
        child->removeClaster(this);
    }
}

void Claster::add(ClasterItem *object) {
    _objects.insert(object->guiId(), object);
    if (auto singlClasterObject = dynamic_cast<ClasterItem*>(object)) {
        singlClasterObject->setClaster(this);
    }
}

void Claster::remove(ClasterItem *object) {
    _objects.remove(object->guiId());
}

void Claster::remove(int id) {
    _objects.remove(id);
}

const QHash<int, ClasterItem *> &Claster::objects() const {
    return _objects;
}
