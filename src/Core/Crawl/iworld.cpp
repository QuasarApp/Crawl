//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "Extensions/claster.h"
#include "iai.h"
#include "iworld.h"
#include "iworlditem.h"
#include <defaultbackgroundai.h>
#include <quasarapp.h>
#include "groundclaster.h"
#include "defaultcontrol.h"
#include "worldstatus.h"
#include "iai.h"
#include "clasteritem.h"
#include "thread"
#include "chrono"
#include "diff.h"

namespace CRAWL {


IWorld::IWorld() {
    qRegisterMetaType<WorldRule::const_iterator>("WorldRule::const_iterator");
    connect(this, &IWorld::sigWorldChanged, this, &IWorld::worldChanged, Qt::QueuedConnection);
}

IWorld::~IWorld() {
    reset();
}

void IWorld::init() {prepare();}

IControl *IWorld::initUserInterface() const {
    return new DefaultControl;
}

void IWorld::render(unsigned int tbfMsec) {

    if (!_running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        return;
    }

    _ItemsMutex.lock();

    for (auto i = _items.begin(); i != _items.end(); ++i) {
        (*i)->render(tbfMsec);

        // intersects event.
        if ((*i)->intersects(*_player)) {
            _player->onIntersects((*i));
        }
    }

    _ItemsMutex.unlock();


    if (_player->isDead()) {
        emit sigGameFinished(_player->getCurrentStatus());
    }

    updateWorld();

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

    setWorldStatus(WorldStatus::Game);
    _backgroundAI->stopAI();
    _player->setControl(_userInterface);


    worldChanged(_worldRules->cbegin());
    setTargetFps(60);
    setRunning(true);

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

    if (_player)
        removeItem(_player->guiId());

    _player = newPlayerObject;
    addItem(_player);

    emit playerChanged();
}

IWorldItem *IWorld::generate(const QString &objectType) const {
    return _registeredTypes.value(objectType, [](){return nullptr;}).operator()();
}

bool IWorld::stop() {
    setRunning(false);
    return true;
}

IAI *IWorld::initBackGroundAI() const {
    return new DefaultBackgroundAI();
}

IWorldItem *IWorld::getItem(int id) const {
    QMutexLocker lock(&_ItemsMutex);

    return _items.value(id, nullptr);
}

bool IWorld::prepare() {

    if (isInit())
        return true;

    _worldRules = initWorldRules();

    setHdr(initHdrBackGround());
    setPlayer(initPlayer());
    _player->initOnWorld(this, _player);
    _userInterface = initUserInterface();
    _backgroundAI = initBackGroundAI();

    if (!isInit()) {
        QuasarAppUtils::Params::log("Failed to init world implementation.");
        reset();
        return false;
    }

    if (!_worldRules->size()) {
        reset();
        return false;
    }

    initPlayerControl(_userInterface);
    initPlayerControl(dynamic_cast<IControl*>(_backgroundAI));

    return true;
}

void IWorld::clearItems() {
    stop();

    while (_items.cbegin() != _items.cend()) {
        removeItem(*_items.cbegin());
    }

    _items.clear();
}

void IWorld::addItem(IWorldItem *obj, QList<int> *addedObjectsList) {
    if (!obj)
        return;

    obj->init();
    Diff diff;

    // Work wih claster
    if (auto claster = dynamic_cast<Claster*>(obj)) {
        for (auto item : claster->objects()) {
            addAtomicItem(item);
            if (item) {
                diff.addedIds.push_back(item->guiId());
            }
        }
    }

    addAtomicItem(obj);
    diff.addedIds.push_back(obj->guiId());

    if (addedObjectsList)
        *addedObjectsList = diff.addedIds;

    emit sigOBjctsListChanged(diff);

}

void IWorld::removeItem(int id, QList<int> *removedObjectsList) {
    removeItem(getItem(id), removedObjectsList);
}

void IWorld::removeItem(IWorldItem* item, QList<int> *removedObjectsList) {

    if (!item)
        return;

    Diff diff;

    // Work wih claster
    if (auto claster = dynamic_cast<Claster*>(item)) {
        const auto copyOfObjectsList = claster->objects();
        for (auto item : copyOfObjectsList) {
            auto clasterItem = dynamic_cast<ClasterItem*>(item);
            if (!clasterItem || clasterItem->parentClastersCount() > 1)
                continue;

            int id = item->guiId();

            removeAtomicItem(item);
            if (removedObjectsList)
                diff.removeIds.push_back(id);

        }
    }

    removeAtomicItem(item);
    diff.removeIds.push_back(item->guiId());

    if (removedObjectsList)
        *removedObjectsList = diff.removeIds;

    emit sigOBjctsListChanged(diff);
}

void IWorld::reset() {

    if (_player) {
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
    setHdr("");

}


void IWorld::addAtomicItem(IWorldItem* obj) {
    if (!obj)
        return;

    QMutexLocker lock(&_ItemsMutex);

    _items.insert(obj->guiId(), obj);
    _itemsGroup.insert(obj->className(), obj->guiId());

    obj->initOnWorld(this, _player);
}

bool IWorld::removeAtomicItem(int id) {
    QMutexLocker lock(&_ItemsMutex);

    auto obj = _items.value(id);

    if (!obj) {
        return false;
    }

    _itemsGroup.remove(obj->className(), id);
    _items.remove(id);

    obj->deleteLater();

    return true;
}

bool IWorld::removeAtomicItem(IWorldItem *obj) {
    if (!obj) {
        return false;
    }

    QMutexLocker lock(&_ItemsMutex);

    _itemsGroup.remove(obj->className(), obj->guiId());
    _items.remove(obj->guiId());

    obj->deleteLater();

    return true;
}

void IWorld::removeAnyItemFromGroup(const QString &group,
                                    QList<int> *removedObjectsList) {
    int anyObjectId = _itemsGroup.value(group);
    removeItem(anyObjectId, removedObjectsList);
}

bool IWorld::running() const {
    return _running;
}

void IWorld::setRunning(bool newRunning) {
    _running = newRunning;
}

int IWorld::targetFps() const {
    return _targetFps;
}

void IWorld::setTargetFps(int newTargetFps) {
    _targetFps = newTargetFps;
}

void IWorld::setHdr(const QString &hdr) {
    if (hdr == _hdrMap)
        return;

    _hdrMap = hdr;
    emit hdrChanged();
}

void IWorld::updateWorld() {

    if (_currendWorldLevel->isEmpty() || !_worldRules || !_player)
        return;

    float distance = _player->position().x();
    auto nextLevel = std::next(_currendWorldLevel);
    if (nextLevel != _worldRules->cend() && distance > nextLevel.key()) {
        emit sigWorldChanged(nextLevel);
    }
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
    runAsBackGround();
}

const QVector3D &IWorld::cameraReleativePosition() const {
    return _cameraReleativePosition;
}

void IWorld::worldChanged(WorldRule::const_iterator iterator) {

    if (_currendWorldLevel == iterator)
        return;

    auto objects = iterator.value();
    objects[_player->className()] = 1;

    for (auto it = objects.begin(); it != objects.end(); ++it) {

        int count = it.value() - _itemsGroup.count(it.key());

        if (count > 0) {
            for ( int i = 0; i < count; ++i ) {
                addItem(generate(it.key()));
            }
        } else {
            for (; count < 0; ++count ) {
                removeAnyItemFromGroup(it.key());
            }
        }
    }

    _currendWorldLevel = iterator;
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


const QString &IWorld::hdr() const {
    return _hdrMap;
}

void IWorld::runAsBackGround() {
    start();

    setWorldStatus(WorldStatus::Background);
    _player->setControl(dynamic_cast<IControl*>(_backgroundAI));

    _backgroundAI->startAI();

    setTargetFps(30);
}

}
