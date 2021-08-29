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

void OfflineStore::init(const ILevel *level) {
    store().unite(level->availableItems());
    store().insert(level->world()->itemId(), level->world());
}

}
