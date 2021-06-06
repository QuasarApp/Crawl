#include "iworld.h"
#include "guiobject.h"
#include <quasarapp.h>

IWorld::IWorld() {

}

IWorld::~IWorld() {
    deinit();
}

void IWorld::render(unsigned int tbfMsec) {

    for (auto i = _items.begin(); i != _items.end(); ++i) {
        (*i).objectPtr->render(tbfMsec);
    }
}

bool IWorld::init() {

    _worldRules = initWorldRules();
    _hdrMap = initHdrBackGround();
    _snake = initPlayer();

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
    delete _snake;

    clearItems();
    _hdrMap = "";

    delete  _worldRules;
}

void IWorld::addItem(const QString& group, GuiObject* obj) {
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
    auto anyObject =_itemsGroup.value(group);
    return removeItem(anyObject);
}

void IWorld::worldChanged(const WorldObjects &objects) {

    for (auto it = objects.begin(); it != objects.end(); ++it) {

        int count = it.value() -_itemsGroup.count(it.key());

        if (count > 0) {
            for ( int i = 0; i < count; ++i ) {
                auto obj = generate(it.key());

                if (!obj) {
                    QuasarAppUtils::Params::log("object not created line:" + QString::fromLatin1(Q_FUNC_INFO),
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

