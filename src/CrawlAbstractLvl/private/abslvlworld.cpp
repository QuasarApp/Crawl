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
#include <snake.h>
#include "Crawl/iworlditem.h"


AbsLvlWorld::AbsLvlWorld() {

}

IPlayer *AbsLvlWorld::initPlayer() const {
    return new Snake();
}

WorldRule *AbsLvlWorld::initWorldRules() {
    return new WorldRule {
        {0, {{registerObject<Baff>(), 1}}},
        {100, {{registerObject<ObstacleBlue>(), 1}}},
        {200, {{registerObject<ObstacleRed>(), 1}}}
    };
}

QString AbsLvlWorld::initHdrBackGround() const {
    return "qrc:/hdr/hdr/plate_absLvl.hdr";
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

IControl *AbsLvlWorld::initUserInterface() const {
    return new AbsLvlControl();
}

void AbsLvlWorld::initPlayerControl(IControl *control) {
    return IWorld::initPlayerControl(control);
}
