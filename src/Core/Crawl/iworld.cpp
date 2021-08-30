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
#include "eventserver.h"
#include "player.h"
#include <QtConcurrent>
#include "snake.h"
#include "store.h"

namespace CRAWL {


IWorld::IWorld() {
    qRegisterMetaType<WorldRule::const_iterator>("WorldRule::const_iterator");
    connect(this, &IWorld::sigWorldChanged, this, &IWorld::worldChanged, Qt::QueuedConnection);

    _eventServer = new EventServer(this);

    connect(_eventServer, &EventServer::sigIntersect, this, &IWorld::onIntersects);
    connect(this, &IWorld::sigOBjctsListChanged, _eventServer, &EventServer::handleAvailableObjectChanges);

}

IWorld::~IWorld() {
    disconnect();

    IWorld::stop();

    clear();

    delete _eventServer;
}

QString IWorld::itemTextType() const {
    return IWorld::typeText();
}

unsigned int IWorld::type() {
    return qHash(IWorld::typeText());
}

QString IWorld::typeText() {
    return "WorldObject";
}

void IWorld::init() {
}

IControl *IWorld::initUserInterface() const {
    return new DefaultControl;
}

void IWorld::render(unsigned int tbfMsec) {

    _ItemsMutex.lock();
    QList<int> toRemove;
    for (auto i = _items.begin(); i != _items.end(); ++i) {
        if ((*i)->destroyIsScheduled())
            toRemove.push_back((*i)->guiId());

        (*i)->render(tbfMsec);
    }

    _ItemsMutex.unlock();

    for (int id: toRemove) {
        if (id == static_cast<IWorldItem *>(player())->guiId()) {
            playerIsDead(static_cast<PlayableObject*>(player()));
        }

        removeItem(id);
    }

    updateWorld();

    int waitTime = 1000 / targetFps() - tbfMsec;
    if (waitTime > 0)
        std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
}

void IWorld::initControl(IControl *control) {
    auto controlObject = dynamic_cast<DefaultControl*>(control);

    if (controlObject) {
        connect(controlObject, &DefaultControl::backToMenu, this, &IWorld::handleStop);
    }
}

bool IWorld::start(const StartData& config) {

    auto player = dynamic_cast<Player*>(userInterface());
    if (!player) {
        QuasarAppUtils::Params::log("Failed to start world. The userIterface control should be children class of the Palyer class",
                                    QuasarAppUtils::Error);

        return false;
    }

    backgroundAI()->stopAI();
    setWorldStatus(WorldStatus::Game);

    auto snakeOject = dynamic_cast<Snake*>(config.snake());
    if (!snakeOject)
        return false;

    setPlayer(snakeOject);

    player->setUserData(config.player());

    worldChanged(worldRules()->cbegin());
    setTargetFps(60);
    _eventServer->start();
    setVisible(true);

    startRenderLoop();

    return true;
}

QObject *IWorld::player() const {
    return _player;
}

void IWorld::setPlayer(QObject *newPlayer) {
    if (_player == newPlayer)
        return;

    auto newPlayerObject = dynamic_cast<PlayableObject*>(newPlayer);
    if (!newPlayerObject) {
        QuasarAppUtils::Params::log("Failed to set player object. The input object is not player.",
                                    QuasarAppUtils::Error);
        return;
    }

    if (_player)
        removeItem(_player->guiId());

    _player = newPlayerObject;
    _player->setposition({0,0,0});
    _player->setControl(userInterface());

    addItem(_player);

    emit playerChanged();
}

IWorldItem *IWorld::generate(const QString &objectType) const {
    return _registeredTypes.value(objectType, [](){return nullptr;}).operator()();
}

bool IWorld::stop() {
    _eventServer->stop();

    stopRenderLoopWithClearItems();
    setVisible(false);

    emit sigGameFinished();
    return true;
}

IAI *IWorld::initBackGroundAI() const {
    return new DefaultBackgroundAI();
}

IWorldItem *IWorld::getItem(int id) const {
    QMutexLocker lock(&_ItemsMutex);

    return _items.value(id, nullptr);
}

void IWorld::clearItems() {

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

void CRAWL::IWorld::clear() {
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
}

void IWorld::reset() {

    stop();

    if (_player) {
        _player = nullptr;
    }

    clear();
    setHdr("");
}


void IWorld::addAtomicItem(IWorldItem* obj) {
    if (!obj)
        return;

    QMutexLocker lock(&_ItemsMutex);

    _items.insert(obj->guiId(), obj);
    _itemsGroup.insert(obj->className(), obj->guiId());

    obj->initOnWorld(this);
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

    if (!obj->isExternal()) {
        obj->deleteLater();
    }

    return true;
}

void IWorld::removeAnyItemFromGroup(const QString &group,
                                    QList<int> *removedObjectsList) {
    int anyObjectId = _itemsGroup.value(group);
    removeItem(anyObjectId, removedObjectsList);
}

void IWorld::startRenderLoop() {
    if (isRendering())
        return;

    _renderLoop = true;
    _renderLoopFuture = QtConcurrent::run([this](){renderLoop();});
}

void IWorld::stopRenderLoopWithClearItems() {
    stopRenderLoop();
    clearItems();
}

void IWorld::stopRenderLoop() {
    _renderLoop = false;
    _renderLoopFuture.waitForFinished();
}

bool IWorld::isRendering() const {
    return _renderLoopFuture.isRunning();
}

void IWorld::renderLoop() {

    while (_renderLoop) {

        quint64 currentTime = QDateTime::currentMSecsSinceEpoch();

        if (!_oldTimeRender) {
            _oldTimeRender = currentTime;
            continue;
        }

        render(currentTime - _oldTimeRender);
        _oldTimeRender = currentTime;
    }
}

const WorldRule *IWorld::worldRules() {

    if (!_worldRules)
        _worldRules = initWorldRules();

    return _worldRules;
}

void IWorld::setVisible(bool visible) {
    if (_visible == visible) {
        return;
    }

    _visible = visible;
    emit visibleChanged();
}

void IWorld::playerIsDead(PlayableObject *) {
    stop();
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

    if (_currendWorldLevel->isEmpty() || !_player)
        return;

    float distance = _player->position().x();
    auto nextLevel = std::next(_currendWorldLevel);
    if (nextLevel != _worldRules->cend() && distance > nextLevel.key()) {
        emit sigWorldChanged(nextLevel);
    }
}

void IWorld::onIntersects(const IWorldItem *trigger, QList<const IWorldItem *> list) {

    for (const IWorldItem* item : list) {
        const_cast<IWorldItem*>(item)->action(const_cast<IWorldItem*>(trigger));
    }
}

const QQuaternion &IWorld::cameraRotation() const {
    return _cameraRotation;
}

void IWorld::setCameraRotation(const QQuaternion &newCameraRotation) {
    if (_cameraRotation == newCameraRotation)
        return;
    _cameraRotation = newCameraRotation;
    emit cameraRotationChanged();
}

IAI *IWorld::backgroundAI() {

    if (!_backgroundAI) {
        _backgroundAI = initBackGroundAI();
        initControl(dynamic_cast<IControl*>(_backgroundAI));
    }

    return _backgroundAI;
}

IControl *IWorld::userInterface() {

    if (!_userInterface) {
        _userInterface = initUserInterface();
        initControl(_userInterface);
    }

    return _userInterface;
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


const QString &IWorld::hdr() {
    if (_hdrMap.isEmpty())
        setHdr(initHdrBackGround());

    return _hdrMap;
}

void IWorld::runAsBackGround() {
    StartData data(nullptr, 0);
    start(data);

    setWorldStatus(WorldStatus::Background);
    _player->setControl(dynamic_cast<IControl*>(_backgroundAI));

    _backgroundAI->startAI();

    setTargetFps(30);
}

QObject *IWorld::getMenu() {
    return userInterface();
}

bool IWorld::visible() const {
    return _visible;
}

}
