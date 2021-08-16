//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "absaluteplate.h"
#include "grees.h"
#include "ground.h"
#include "nest.h"

#include <Crawl/day.h>
#include <Crawl/moon.h>
#include <Crawl/sun.h>

namespace JungleLvl {

Nest::Nest(IWorld *mainWorld): CRAWL::IPreviewScaneWorld(mainWorld) {

}

CRAWL::WorldRule *Nest::initWorldRules() {
    using Day = CRAWL::Day<CRAWL::Sun, CRAWL::Moon>;

    return new CRAWL::WorldRule {
        {0, {
                {registerObject<AbsalutePlate>(), 1},
                {registerObject<Day>(), 1},
                {registerObject<Ground>(), 1},
                {registerObject<Grees>(), 500}
            }
        }
    };
}

QString Nest::initHdrBackGround() const {
    return "";
}
}
