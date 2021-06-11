#include "iworld.h"
#include "iworlditem.h"
#include <quasarapp.h>
#include "iground.h"

IWorld::IWorld() {

}

IWorld::~IWorld() {
    deinit();
}

IControl *IWorld::initUserInterface() const {
    TO-DO
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

bool IWorld::start() {
    _player->setposition({0,0,0});
    _player->setSpeed(0);


    return true;
}

const IWorldItem *IWorld::getItem(int id) const {
    return _items.value(id, {}).objectPtr;
}

bool IWorld::init() {

    _worldRules = initWorldRules();
    _hdrMap = initHdrBackGround();
    _player = initPlayer();
    _player->initOnWorld(this, _player);
    _userInterface = initUserInterface();

    setCameraReleativePosition(initCameraPosition());

    if (!_worldRules->size())
        return false;

    worldChanged(*_worldRules->begin());

    return true;
}

void IWorld::clearItems() {
    for (const auto& item : qAsConst(_items)) {
        delete item.objectPtr;
    }

    _items.clear();
}

void IWorld::deinit() {
    delete _player;

    clearItems();
    _hdrMap = "";

    delete  _worldRules;
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

bool IWorld::removeAnyItemFromGroup(const QString &group) {
    auto anyObject = _itemsGroup.value(group);
    return removeItem(anyObject);
}

IControl *IWorld::userInterface() const {
    return _userInterface;
}

void IWorld::setCameraReleativePosition(const QVector3D &newCameraReleativePosition) {
    if (_cameraReleativePosition == newCameraReleativePosition)
        return;

    _cameraReleativePosition = newCameraReleativePosition;
    emit cameraReleativePositionChanged();
}

const QVector3D &IWorld::cameraReleativePosition() const {
    return _cameraReleativePosition;
}

const QString &IWorld::hdrMap() const {
    return _hdrMap;
}

void IWorld::worldChanged(const WorldObjects &objects) {

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
            }
        } else {
            for (; count < 0; ++count ) {
                if (!removeAnyItemFromGroup(it.key())) {
                    QuasarAppUtils::Params::log("World::changeCountObjects error delete object!",
                                                QuasarAppUtils::Warning);
                    break;
                }
            }
        }
    }
}

