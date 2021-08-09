//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "iworlditem.h"
#include "iworld.h"
#include "quasarapp.h"

namespace CRAWL {


IWorldItem::IWorldItem(const QString& name,
                       const QString& viewTempalte,
                       QObject *ptr):
    GuiObject(name, viewTempalte, ptr) {

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
    if (_playerObject->position().distanceToPoint(position()) >
            _world->cameraReleativePosition().z() * 3) {
        respawn();
    }
}

void IWorldItem::init() {}

void IWorldItem::initOnWorld(const IWorld *world, const IWorldItem * player) {
    _world = world;
    _playerObject = player;
}

int IWorldItem::supportedEvents() const {
    return _supportedEvents;
}

bool IWorldItem::isSopportEvent(int event) const {
    return (_supportedEvents & event) == event;
}

void IWorldItem::destroy() {
    _fDistroy = true;
}

void IWorldItem::respawn() {
    float dX = _world->cameraReleativePosition().z() * 2 +
            (rand() % static_cast<int>(_world->cameraReleativePosition().z()));

    setX(_playerObject->position().x() + dX);

    float dY = (rand() % static_cast<int>(_world->cameraReleativePosition().z() * 3)
                                         - _world->cameraReleativePosition().z() * 1.5);

    setY(_playerObject->position().y() + dY);
}

bool IWorldItem::destroyIsScheduled() const {
    return _fDistroy;
}

void IWorldItem::action(IWorldItem *) {

}

void IWorldItem::setSupportedEvents(int newSupportedEvents) {
    _supportedEvents = newSupportedEvents;
}

void IWorldItem::addSupportOfEvent(int newSupportedEvent) {
    _supportedEvents = _supportedEvents | newSupportedEvent;
}

void IWorldItem::dropSupportOfEvent(int depricatedEvent) {
    _supportedEvents = _supportedEvents & (~depricatedEvent);
}

bool IWorldItem::isDecorative() const {
    return _fDecorative;
}

void IWorldItem::setFDecorative(bool newFDecorative) {
    _fDecorative = newFDecorative;
}

const IWorld *IWorldItem::world() const {
    return _world;
}

}
