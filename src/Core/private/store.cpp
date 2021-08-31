//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "store.h"

#include <Crawl/iitem.h>
namespace CRAWL {

Store::Store()
{

}

bool Store::buy(User &buyer, int itemId) {

    auto item = getItemById(itemId);

    if (buyer.getTier() < item->requiredTier()) {
        return false;
    }

    if (buyer.getMoney() < item->cost()) {
        return false;
    }

    buyer.setMoney(buyer.getMoney() - item->cost());
    buyer.unclokItem(itemId);

    return true;
}

IItem *Store::getItemById(int id) const {
    return _all.value(id, nullptr);
}

int Store::size() const {
    return _all.size();
}

QList<int> Store::keysList() const {
    return QList<int>{_all.keyBegin(), _all.keyEnd()};
}

QList<int> Store::keysListByType(unsigned int type, const User *user) const {


    auto types = _store[type];

    if (!user) {
        return QList<int>{types.keyBegin(), types.keyEnd()};
    }

    QList<int> result;

    for (int id : user->unlockedItems()) {
        if (types.contains(id)) {
            result.push_back(id);
        }
    }

    return result;
}

QHash<int, IItem *> Store::getItemsByType(unsigned int type, const User *user) const {
    auto types = _store[type];

    if (!user) {
        return QHash<int, IItem *>{types.begin(), types.end()};
    }

    QHash<int, IItem *> result;

    for (int id : user->unlockedItems()) {
        if (IItem* item = types.value(id, nullptr)) {
            result.insert(id, item);
        }
    }

    return result;
}

void Store::addItem(IItem *item) {
    if (item) {
        _store[item->itemType()][item->itemId()] = item;
        _all[item->itemId()] = item;
        item->setStore(this);
    }
}
}
