//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "iworlditem.h"
#include "iworld.h"
#include "quasarapp.h"

IWorldItem::IWorldItem() {

}

const IWorldItem *IWorldItem::getItem(int id) const {
    if (!_world) {
        QuasarAppUtils::Params::log("You try get object in the no initialized _itemWorld object.",
                                    QuasarAppUtils::Error);
        return nullptr;
    }

    return _world->getItem(id);
}

const IWorldItem *IWorldItem::getPlayer() const {
    return _playerObject;
}

void IWorldItem::render(unsigned int) {
    if (_playerObject->position().x() - position().x() >
            _world->cameraReleativePosition().z() * 2) {
        setX(_playerObject->position().x() + _world->cameraReleativePosition().z() * 4);

        float dY = rand() % static_cast<int>(_world->cameraReleativePosition().z() * 2
                                             - _world->cameraReleativePosition().z());

        setY(_playerObject->position().y() + dY);
    }
}

void IWorldItem::initOnWorld(const IWorld *world, const IWorldItem * player) {
    _world = world;
    _playerObject = player;
}

const IWorld *IWorldItem::world() const {
    return _world;
}
