//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "baff.h"
#include "obstacleblue.h"
#include "obstaclered.h"
#include "abslvlcontrol.h"
#include "abslvlworld.h"
#include <abslvlsnake.h>
#include "Crawl/iworlditem.h"

#include "Crawl/defaultlight.h"


namespace AbstractLvl {

AbsLvlWorld::AbsLvlWorld() {
    setCameraReleativePosition({20,0,100});
    setCameraRotation(QQuaternion::fromEulerAngles({0,0,0}));
}

CRAWL::WorldRule *AbsLvlWorld::initWorldRules() {

    return new CRAWL::WorldRule {

        {0,
            {
                {registerObject<Baff>(), 10}, {registerObject<CRAWL::DefaultLight>(), 1}
            }
        },

        {20,
            {
                {registerObject<ObstacleBlue>(), 10}, {registerObject<CRAWL::DefaultLight>(), 1}
            }
        },

        {30,
            {
                {registerObject<ObstacleRed>(), 40}, {registerObject<CRAWL::DefaultLight>(), 1}
            }
        }

    };
}

QString AbsLvlWorld::initHdrBackGround() const {
    return "qrc:/hdr/hdr/plate_absLvl.hdr";
}

QString AbsLvlWorld::description() const {
    return tr("This a abstract lvl");
}

QString AbsLvlWorld::image() const {
    return "qrc:/hdr/hdr/testHDR.jpg";

}

QString AbsLvlWorld::itemName() const {
    return tr("AbstractLvl");
}

int AbsLvlWorld::cost() const {
    return 0;
}

CRAWL::IControl *AbsLvlWorld::initUserInterface() const {
    return new AbsLvlControl();
}

void AbsLvlWorld::initControl(CRAWL::IControl *control) {
    return IWorld::initControl(control);
}

QString AbsLvlWorld::itemTextId() const {
    return "AbstractLevel";
}

int AbsLvlWorld::requiredTier() const {
    return 0;
}

}
