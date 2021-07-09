//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "ground.h"

Ground::Ground() : CRAWL::GroundClaster("JungelGroud") {
    setMash("#Rectangle");
    setSize({100,100, 100});
}

void Ground::onIntersects(const IWorldItem *item) {

}
