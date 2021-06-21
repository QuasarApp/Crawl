//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "claster.h"
#include "iai.h"
#include "iworld.h"
#include "iworlditem.h"
#include <defaultbackgroundai.h>
#include <quasarapp.h>
#include "iground.h"
#include "defaultcontrol.h"
#include "worldstatus.h"
#include "iai.h"
#include "clasteritem.h"
#include "thread"
#include "chrono"

IWorld::IWorld() {

}

IWorld::~IWorld() {
    deinit();
}

IControl *IWorld::initUserInterface() const {
    return new DefaultControl;
}

void IWorld::render(unsigned int tbfMsec) {

    _ItemsMutex.lock();

    for (auto i = _items.begin(); i != _items.end(); ++i) {
        (*i)->render(tbfMsec);

        // intersects event.
        if ((*i)->intersects(*_player)) {
            _player->onIntersects((*i));
        }
    }

    if (_player->isDead()) {
        emit sigGameFinished(_player->getCurrentStatus());
    }

    _ItemsMutex.unlock();

    int waitTime = 1000 / _targetFps - tbfMsec;
    if (waitTime > 0)
        std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
}

void IWorld::initPlayerControl(IControl *control) {
    auto controlObject = dynamic_cast<DefaultControl*>(control);

    if (controlObject) {
        connect(controlObject, &DefaultControl::backToMenu, this, &IWorld::handleStop);
    }
}

bool IWorld::start() {
    _player->setposition({0,0,0});
    _player->setSpeed(0);

    setWorldStatus(WorldStatus::Game);
    _backgroundAI->stopAI();
    _player->setControl(_userInterface);


    worldChanged(*_worldRules->begin());
    setTargetFps(60);
    return true;
}

QObject *IWorld::player() const {
    return _player;
}

void IWorld::setPlayer(QObject *newPlayer) {
    if (_player == newPlayer)
        return;

    auto newPlayerObject = dynamic_cast<IPlayer*>(newPlayer);
    if (!newPlayerObject) {
        QuasarAppUtils::Params::log("Failed to set player object. The input object is not player.",
                                    QuasarAppUtils::Error);
        return;
    }

    if (_player) {
        removeIAtomicItem(_player->guiId());
    }

    _player = newPlayerObject;
    addAtomicItem(_player);

    emit playerChanged();
}

IWorldItem *IWorld::generate(const QString &objectType) const {
    return _registeredTypes.value(objectType, [](){return nullptr;}).operator()();
}

bool IWorld::stop() {
    start();

    setWorldStatus(WorldStatus::Background);
    _player->setControl(dynamic_cast<IControl*>(_backgroundAI));

    _backgroundAI->startAI();

    setTargetFps(30);

    return true;
}

IAI *IWorld::initBackGroundAI() const {
    return new DefaultBackgroundAI();
}

IWorldItem *IWorld::getItem(int id) const {
    QMutexLocker lock(&_ItemsMutex);

    return _items.value(id, nullptr);
}

bool IWorld::init() {

    if (isInit())
        return true;

    _worldRules = initWorldRules();

    _hdrMap = initHdrBackGround();
    setPlayer(initPlayer());
    _player->initOnWorld(this, _player);
    _userInterface = initUserInterface();
    _backgroundAI = initBackGroundAI();

    if (!isInit()) {
        QuasarAppUtils::Params::log("Failed to init world implementation.");
        deinit();
        return false;
    }

    if (!_worldRules->size()) {
        deinit();
        return false;
    }

    initPlayerControl(_userInterface);
    initPlayerControl(dynamic_cast<IControl*>(_backgroundAI));

    return true;
}

void IWorld::clearItems() {
    QMutexLocker lock(&_ItemsMutex);

    for (const auto& item : qAsConst(_items)) {
        delete item;
    }

    _items.clear();
}

void IWorld::addItem(IWorldItem *obj, QList<int> *addedObjectsList) {
    if (!obj)
        return;

    // Work wih claster
    if (auto claster = dynamic_cast<Claster*>(obj)) {
        for (auto item : claster->objects()) {
            addAtomicItem(item);
            if (item && addedObjectsList) {
                addedObjectsList->push_back(item->guiId());
            }
        }
    }

    addAtomicItem(obj);
    if (addedObjectsList)
        addedObjectsList->push_back(obj->guiId());

}

void IWorld::removeItem(int id, QList<int> *removedObjectsList) {

    auto obj = getItem(id);

    if (!obj)
        return;

    // Work wih claster
    if (auto claster = dynamic_cast<Claster*>(obj)) {
        auto copyOfObjectsList = claster->objects();
        for (auto item : copyOfObjectsList) {
            if (!item || !item->parentClastersCount())
                continue;

            int id = item->guiId();

            removeIAtomicItem(item);
            if (removedObjectsList)
                removedObjectsList->push_back(id);

        }
    }

    addAtomicItem(obj);
    if (removedObjectsList)
        removedObjectsList->push_back(obj->guiId());

}

void IWorld::deinit() {
    if (_player) {
        delete _player;
        _player = nullptr;
    }

    if (_worldRules) {
        delete _worldRules;
        _worldRules = nullptr;
    }

    if (_userInterface) {
        delete _userInterface;
        _userInterface = nullptr;
    }

    if (_backgroundAI) {
        delete _backgroundAI;
        _backgroundAI = nullptr;
    }

    clearItems();
    _hdrMap = "";

}


void IWorld::addAtomicItem(IWorldItem* obj) {
    if (!obj)
        return;

    QMutexLocker lock(&_ItemsMutex);

    _items.insert(obj->guiId(), obj);
    _itemsGroup.insert(obj->className(), obj->guiId());

    obj->initOnWorld(this, _player);
}

bool IWorld::removeIAtomicItem(int id) {
    QMutexLocker lock(&_ItemsMutex);

    auto obj = _items.value(id);

    if (!obj) {
        return false;
    }

    _itemsGroup.remove(obj->className(), id);
    _items.remove(id);

    delete obj;

    return true;
}

bool IWorld::removeIAtomicItem(IWorldItem *obj) {
    if (!obj) {
        return false;
    }

    QMutexLocker lock(&_ItemsMutex);

    _itemsGroup.remove(obj->className(), obj->guiId());
    _items.remove(obj->guiId());

    delete obj;

    return true;
}

void IWorld::removeAnyItemFromGroup(const QString &group,
                                    QList<int> *removedObjectsList) {
    int anyObjectId = _itemsGroup.value(group);
    removeItem(anyObjectId, removedObjectsList);
}

int IWorld::targetFps() const {
    return _targetFps;
}

void IWorld::setTargetFps(int newTargetFps) {
    _targetFps = newTargetFps;
}

const QQuaternion &IWorld::cameraRatation() const {
    return _cameraRatation;
}

void IWorld::setCameraRatation(const QQuaternion &newCameraRatation) {
    if (_cameraRatation == newCameraRatation)
        return;
    _cameraRatation = newCameraRatation;
    emit cameraRatationChanged();
}

IAI *IWorld::backgroundAI() const {
    return _backgroundAI;
}

IControl *IWorld::userInterface() const {
    return _userInterface;
}

bool IWorld::isInit() const {
    return _userInterface && _player && _worldRules && _backgroundAI;
}

void IWorld::setCameraReleativePosition(const QVector3D &newCameraReleativePosition) {
    if (_cameraReleativePosition == newCameraReleativePosition)
        return;

    _cameraReleativePosition = newCameraReleativePosition;
    emit cameraReleativePositionChanged();
}

void IWorld::handleStop() {
    stop();
}

const QVector3D &IWorld::cameraReleativePosition() const {
    return _cameraReleativePosition;
}

const QString &IWorld::hdrMap() const {
    return _hdrMap;
}

void IWorld::worldChanged(const WorldObjects &objects) {

    Diff diff;
    for (auto it = objects.begin(); it != objects.end(); ++it) {

        int count = it.value() - _itemsGroup.count(it.key());

        if (count > 0) {
            for ( int i = 0; i < count; ++i ) {
                addItem(generate(it.key()), &diff.addedIds);
            }
        } else {
            for (; count < 0; ++count ) {
                removeAnyItemFromGroup(it.key(), &diff.removeIds);
            }
        }
    }

    if (diff.addedIds.size() || diff.removeIds.size())
        emit sigOBjctsListChanged(diff);
}


int IWorld::wordlStatus() const {
    return _worldStatus;
}

void IWorld::setWorldStatus(int newWorldStatus) {
    if (_worldStatus == newWorldStatus) {
        return;
    }
    _worldStatus = newWorldStatus;
    emit worldStatusChanged();
}

