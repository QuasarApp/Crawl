#include "worldviewdata.h"
#include "Crawl/iworld.h"

WorldViewData::WorldViewData(const IWorld *data) {
    setWorldObject(data);
}

QString WorldViewData::name() const {
    if (_worldObject) {
        return _worldObject->name();
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
        return _worldObject->costToUnlock();
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
        return _worldObject->imagePreview();
    }

    return "";
}

void WorldViewData::setWorldObject(const IWorld *newWorldObject) {
    if (_worldObject == newWorldObject)
        return;

    _worldObject = newWorldObject;
    emit dataChanged();

}
