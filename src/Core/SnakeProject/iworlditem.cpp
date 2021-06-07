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

void IWorldItem::initOnWorld(const IWorld *world) {
    _world = world;
}
