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

bool Store::init(const QHash<int, const IItem *> &availabelItems) {
    _store = availabelItems;

    return true;
}

const IItem *Store::getItemById(int id) const {
    return _store.value(id, nullptr);
}
}
