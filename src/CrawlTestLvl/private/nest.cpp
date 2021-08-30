//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#
#include "background.h"
#include "box.h"
#include "nest.h"

#include <Crawl/day.h>
#include <Crawl/dynamicwint.h>
#include <Crawl/fire.h>
#include <Crawl/moon.h>
#include <Crawl/sun.h>

namespace TestLvl {

Nest::Nest(): CRAWL::IPreviewScaneWorld() {

}

CRAWL::WorldRule *Nest::initWorldRules() {
    using Day = CRAWL::Day<CRAWL::Sun, CRAWL::Moon>;

    return new CRAWL::WorldRule {
        {0, {{registerObject<Box>(), 3},
             {registerObject<CRAWL::Fire>(), 2},
             {registerObject<CRAWL::DynamicWint>(), 1},

             {registerObject<Background>(), 1},
             {registerObject<Day>(), 1}}}
    };
}

QString Nest::initHdrBackGround() const {
    return "";
}

CRAWL::IWorldItem *Nest::generate(const QString &objectType) const {
    auto object = IPreviewScaneWorld::generate(objectType);

    return object;
}


}
