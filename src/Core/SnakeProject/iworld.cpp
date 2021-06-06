#include "iworld.h"
#include "itemworld.h"

IWorld::IWorld() {

}

IWorld::~IWorld() {
    deinit();
}

bool IWorld::init() {

}

void IWorld::deinit() {
    delete _snake;
    for (const auto& item : qAsConst(items)) {
        delete item;
    }

    items.clear();

    spead = 0;
    currentLong = 0;
    _hdrMap = "";
    delete  _worldRules;
}
