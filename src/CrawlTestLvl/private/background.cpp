//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "background.h"
#include "plate.h"

namespace TestLvl {

Background::Background(): CRAWL::GroundClaster("TestBackground") {
    registerItemType<Plate>();
}

void Background::onIntersects(const IWorldItem *item) {
    Q_UNUSED(item)
}

unsigned int Background::itemsCount() const {
    return 3;
}

}
