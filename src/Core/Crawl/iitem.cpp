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

QList<const IItem *> IItem::childItems() const {
    return _childs;
}

QMultiHash<int, const IItem *> IItem::childItemsRecursive() const {
    QMultiHash<int, const IItem *> result;

    for (const IItem* item : _childs) {
        result.unite(item->childItemsRecursive());
    }

    result.insert(itemId(), this);
    return result;
}

void IItem::addChildItem(const IItem *item) {
    _childs.push_back(item);
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
}
