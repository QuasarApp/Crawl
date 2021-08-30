//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "offlinestore.h"

#include <Crawl/ilevel.h>
#include "Crawl/iworld.h"

namespace CRAWL {

OfflineStore::OfflineStore() {

}

void OfflineStore::addLevel(const ILevel *level) {

    for (auto item : qAsConst(level->availableItems())) {
        item->setStore(this);
        store().insert(item->itemId(), item);
    }

    store().insert(level->world()->itemId(), level->world());
    level->world()->setStore(this);
}

}
