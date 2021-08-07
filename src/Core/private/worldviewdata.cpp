//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "worldviewdata.h"
#include "Crawl/iworld.h"
namespace CRAWL {

WorldViewData::WorldViewData(const IWorld *data) {
    setWorldObject(data);
}

QString WorldViewData::name() const {
    if (_worldObject) {
        return _worldObject->itemName();
    }

    return "";
}

QString WorldViewData::desc() const {
    if (_worldObject) {
        return _worldObject->description();
    }

    return "";
}

int WorldViewData::cost() const {
    if (_worldObject) {
        return _worldObject->cost();
    }

    return 0;
}

bool WorldViewData::unlocked() const {
    return m_unlocked || !cost();
}

void WorldViewData::setUnlocked(bool newUnlocked) {
    if (m_unlocked == newUnlocked)
        return;
    m_unlocked = newUnlocked;
    emit unlockedChanged();
}

QString WorldViewData::image() const {
    if (_worldObject) {
        return _worldObject->image();
    }

    return "";
}

void WorldViewData::setWorldObject(const IWorld *newWorldObject) {
    if (_worldObject == newWorldObject)
        return;

    _worldObject = newWorldObject;
    emit dataChanged();

}
}
