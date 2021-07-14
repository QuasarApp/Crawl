//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "ground.h"
#include "groundplate.h"
namespace JungleLvl {

Ground::Ground() : CRAWL::GroundClaster("JungelGroud") {
    registerItemType<GroundPlate>();
}

void Ground::onIntersects(const IWorldItem *) {

}

unsigned int Ground::itemsCount() const {
    return 3;
}
}
