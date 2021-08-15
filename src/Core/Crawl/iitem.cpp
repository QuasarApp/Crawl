//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "iitem.h"
#include <QHash>

namespace CRAWL {

IItem::IItem() {

}

const QHash<int, const IItem *>& IItem::childItems() const {
    return _childs;
}

QMultiHash<int, const IItem *>  IItem::childItemsRecursive() const {
    QMultiHash<int, const IItem *>  result;

    for (const IItem* item : _childs) {
        result.unite(item->childItemsRecursive());
    }

    result.insert(itemId(), this);
    return result;
}

void IItem::addChildItem(const IItem *item) {
    _childs.insert(item->itemId(), item);
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
    _activeItems += item;
}

void IItem::deactivate(int item) {
    _activeItems -= item;
}

bool IItem::isActive(int item) {
    return _childs.contains(item) && _activeItems.contains(item);
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

}
