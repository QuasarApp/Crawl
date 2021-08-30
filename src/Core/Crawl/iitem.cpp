//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "iitem.h"
#include <QHash>
#include "quasarapp.h"

namespace CRAWL {

IItem::IItem() {

}

const QHash<int, ChildItemAction> &IItem::childItems() const {
    return _childs;
}

void IItem::registerActions(int itemID, const ChildItemAction &action) {
    _childs[itemID] = action;
}

ChildItemAction IItem::getChildActions(int id) const {
    return childItems().value(id, {});
}

unsigned int IItem::itemId() {
    if (_id) {
        return _id;
    }

    _id = qHash(itemTextId());
    return _id;
}

unsigned int IItem::itemId() const {
    if (_id) {
        return _id;
    }

    return qHash(itemTextId());
}

const QSet<int> &IItem::activeItems() const {
    return _activeItems;
}

void IItem::setActiveItems(const QSet<int> &newActiveItems) {
    _activeItems = newActiveItems;
}

void IItem::activate(int item) {

    if (_activeItems.contains(item)) {
        return;
    }

    _activeItems += item;

    auto actions = _childs.value(item);
    if (actions.isValid()) {
       actions._onAdded();
    }
}

void IItem::deactivate(int item) {
    if (_activeItems.contains(item)) {
        return;
    }

    _activeItems -= item;

    auto actions = _childs.value(item);
    if (actions.isValid()) {
       actions._onDropped();
    }
}

bool IItem::isActive(int item) {
    return _childs.contains(item) && _activeItems.contains(item);
}

const Store *IItem::store() const {
    return _store;
}

void IItem::setStore(const Store *newStore) {
    _store = newStore;
}

unsigned int IItem::itemType() {
    if (_typeItem) {
        return _typeItem;
    }

    _typeItem = qHash(itemTextType());
    return _typeItem;
}

unsigned int IItem::itemType() const {
    if (_typeItem) {
        return _typeItem;
    }

    return qHash(itemTextType());
}

bool ChildItemAction::isValid() const {
    return _onAdded && _onDropped;
}

}
