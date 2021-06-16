#include "iai.h"
#include "iworld.h"
#include "iworlditem.h"
#include <defaultbackgroundai.h>
#include <quasarapp.h>
#include "iground.h"
#include "defaultcontrol.h"
#include "worldstatus.h"
#include "iai.h"

IWorld::IWorld() {

}

IWorld::~IWorld() {
    deinit();
}

IControl *IWorld::initUserInterface() const {
    return new DefaultControl;
}

void IWorld::render(unsigned int tbfMsec) {

    for (auto i = _items.begin(); i != _items.end(); ++i) {
        (*i).objectPtr->render(tbfMsec);

        // intersects event.
        if ((*i).objectPtr->intersects(*_player)) {
            _player->onIntersects((*i).objectPtr);
        }
    }

    if (_player->isDead()) {
        emit sigGameFinished(_player->getCurrentStatus());
    }
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

    return true;
}

bool IWorld::stop() {
    start();

    setWorldStatus(WorldStatus::Background);
    _player->setControl(dynamic_cast<IControl*>(_backgroundAI));

    _backgroundAI->startAI();

    return true;
}

IAI *IWorld::initBackGroundAI() const {
    return new DefaultBackgroundAI();
}

IWorldItem *IWorld::getItem(int id) const {
    return _items.value(id, {}).objectPtr;
}

bool IWorld::init() {

    if (isInit())
        return true;

    _worldRules = initWorldRules();
    _hdrMap = initHdrBackGround();
    _player = initPlayer();
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
    generateGround();

    return true;
}

void IWorld::clearItems() {
    for (const auto& item : qAsConst(_items)) {
        delete item.objectPtr;
    }

    _items.clear();
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

void IWorld::generateGround() {
    int count = 10;

    QVector3D position = {0,0,0};
    float increment = cameraReleativePosition().z() * 2;

    while (count--) {
        auto item = generateGroundTile();
        item->initOnWorld(this, _player);

        position.setX(position.x() + increment);
        item->setposition(position);
        addItem("groundTile", item);
    }
}

void IWorld::addItem(const QString& group, IWorldItem* obj) {
    _items.insert(obj->guiId(), WorldObjectWraper{obj, group});
    _itemsGroup.insert(group, obj->guiId());
}

bool IWorld::removeItem(int id) {
    auto obj = _items.value(id);

    if (!obj.objectPtr) {
        return false;
    }

    _itemsGroup.remove(obj.groupName, id);
    _items.remove(id);

    delete obj.objectPtr;

    return true;
}

int IWorld::removeAnyItemFromGroup(const QString &group) {
    int anyObjectId = _itemsGroup.value(group);
    if (!removeItem(anyObjectId)) {
        return false;
    }

    return anyObjectId;
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
                IWorldItem *obj = generate(it.key());

                obj->initOnWorld(this, _player);

                if (!obj) {
                    QuasarAppUtils::Params::log("object not created line:" +
                                                QString::fromLatin1(Q_FUNC_INFO),
                                                QuasarAppUtils::Warning);
                    break;
                }

                addItem(it.key(), obj);
                diff.addedIds.append(obj->guiId());
            }
        } else {
            for (; count < 0; ++count ) {
                int removedObjectId = removeAnyItemFromGroup(it.key());
                if (!removedObjectId) {
                    QuasarAppUtils::Params::log("World::changeCountObjects error delete object!",
                                                QuasarAppUtils::Warning);
                    break;
                }
                diff.removeIds.append(removedObjectId);
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
