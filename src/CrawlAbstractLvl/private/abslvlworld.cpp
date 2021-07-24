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

namespace AbstractLvl {

AbsLvlWorld::AbsLvlWorld() {
    setCameraReleativePosition({50,0,150});
    setCameraRatation(QQuaternion::fromEulerAngles({0,0,0}));
}

CRAWL::IPlayer *AbsLvlWorld::initPlayer() const {
    return new AbsLvlSnake();
}

CRAWL::WorldRule *AbsLvlWorld::initWorldRules() {
    return new CRAWL::WorldRule {

        {0,
            {
                {registerObject<Baff>(), 1}
            }
        },

        {200,
            {
                {registerObject<ObstacleBlue>(), 1}
            }
        },

        {300,
            {
                {registerObject<ObstacleRed>(), 4}
            }
        }

    };
}

QString AbsLvlWorld::initHdrBackGround() const {
    return "qrc:/hdr/hdr/testHDR.hdr";
}

QString AbsLvlWorld::description() const {
    return tr("This a abstract lvl");
}

QString AbsLvlWorld::imagePreview() const {
    return "qrc:/hdr/hdr/testHDR.jpg";

}

QString AbsLvlWorld::name() const {
    return tr("AbstractLvl");
}

int AbsLvlWorld::costToUnlock() const {
    return 0;
}

CRAWL::IControl *AbsLvlWorld::initUserInterface() const {
    return new AbsLvlControl();
}

void AbsLvlWorld::initPlayerControl(CRAWL::IControl *control) {
    return IWorld::initPlayerControl(control);
}

}
