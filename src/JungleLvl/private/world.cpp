//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "grees.h"
#include "ground.h"
#include "longgress.h"
#include "snake.h"
#include "tree.h"
#include "world.h"
#include "Crawl/iworlditem.h"
#include "ivy.h"
#include "plant.h"
#include "stone.h"
#include "wood.h"
#include "redegg.h"
#include "purpleegg.h"
#include "blueegg.h"

#include <Crawl/snake.h>
namespace JungleLvl {

World::World() {
    setCameraReleativePosition({0,0,100});
    setCameraRatation(QQuaternion::fromEulerAngles({0,0,-90}));
}

CRAWL::WorldRule *World::initWorldRules() {
    return new CRAWL::WorldRule {
        {0, {
                {registerObject<Ground>(), 1},
                {registerObject<Grees>(), 500},
                {registerObject<LongGress>(), 100}


            }
        },
        {5000, {
                {registerObject<Ground>(), 1},
                {registerObject<Grees>(), 500},
                {registerObject<LongGress>(), 100},
                {registerObject<Plant>(), 20},
                {registerObject<Wood>(), 25},


            }
        },
        {10000, {
                {registerObject<Ground>(), 1},
                {registerObject<Grees>(), 500},
                {registerObject<LongGress>(), 100},
                {registerObject<Tree>(), 50},
                {registerObject<Plant>(), 20},
                {registerObject<Ivy>(), 25},
                {registerObject<Stone>(), 25},
                {registerObject<Wood>(), 25},
                {registerObject<RedEgg>(), 5},
                {registerObject<PurpleEgg>(), 5},
                {registerObject<BlueEgg>(), 5},

            }
        }
    };
}

QString World::initHdrBackGround() const {
    return "qrc:/hdr/hdr/Jungle.hdr";
}

QString World::description() const {
    return tr("Jungle world.");
}

QString World::imagePreview() const {
    return "qrc:/hdr/hdr/jungleBanner.jpg";
}

QString World::name() const {
    return tr("Jungle");
}

int World::costToUnlock() const {
    return 0;
}

CRAWL::IControl *World::initUserInterface() const {
    return IWorld::initUserInterface();
}

void World::initPlayerControl(CRAWL::IControl *control) {
    return IWorld::initPlayerControl(control);
}

CRAWL::IPlayer *World::initPlayer() const {
    return new Snake();
}

CRAWL::IAI *World::initBackGroundAI() const {
    return IWorld::initBackGroundAI();
}

void World::handleXViewChanged(double dx) {
    auto eilorRatation = cameraRatation().toEulerAngles();
    eilorRatation.setX(eilorRatation.x() + dx);
    setCameraRatation(QQuaternion::fromEulerAngles(eilorRatation));
}

void World::handleYViewChanged(double dy) {
    auto eilorRatation = cameraRatation().toEulerAngles();
    eilorRatation.setY(eilorRatation.y() + dy );
    setCameraRatation(QQuaternion::fromEulerAngles(eilorRatation));
}

}
