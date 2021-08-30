//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "absnest.h"
#include "obstacleblue.h"

#include <Crawl/defaultlight.h>

namespace AbstractLvl {

AbsNest::AbsNest(): CRAWL::IPreviewScaneWorld() {

}

CRAWL::WorldRule *AbsNest::initWorldRules() {
    return new CRAWL::WorldRule {
        {0,
            {
                {registerObject<ObstacleBlue>(), 1},
                {registerObject<CRAWL::DefaultLight>(), 1}
            }
        }

    };
}

QString AbsNest::initHdrBackGround() const {
    return "";
}

}
