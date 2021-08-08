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
#include "absaluteplate.h"
#include "Crawl/sun.h"
#include "Crawl/moon.h"

#include <Crawl/day.h>
#include <Crawl/defaultlight.h>
#include <Crawl/snake.h>
namespace JungleLvl {

World::World() {
    setCameraReleativePosition({50,0,100});
    setCameraRotation(QQuaternion::fromEulerAngles({0,0,0}));
}

CRAWL::WorldRule *World::initWorldRules() {

    using Day = CRAWL::Day<CRAWL::Sun, CRAWL::Moon>;

    return new CRAWL::WorldRule {
        {0, {
                {registerObject<AbsalutePlate>(), 1},
                {registerObject<Day>(), 1},
                {registerObject<Ground>(), 1},
                {registerObject<Grees>(), 500},
                {registerObject<LongGress>(), 100},


            }
        },
        {1000, {
                {registerObject<AbsalutePlate>(), 1},
                {registerObject<Day>(), 1},
                {registerObject<Ground>(), 1},
                {registerObject<Grees>(), 500},
                {registerObject<LongGress>(), 100},
                {registerObject<Plant>(), 20},
                {registerObject<Wood>(), 25},


            }
        },
        {2000, {
                {registerObject<AbsalutePlate>(), 1},
                {registerObject<Day>(), 1},
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

QString World::image() const {
    return "qrc:/hdr/hdr/jungleBanner.jpg";
}

QString World::itemName() const {
    return tr("Jungle");
}

int World::cost() const {
    return 0;
}

CRAWL::IControl *World::initUserInterface() const {
    return IWorld::initUserInterface();
}

void World::initPlayerControl(CRAWL::IControl *control) {
    return IWorld::initPlayerControl(control);
}

CRAWL::PlayableObject *World::initPlayer() const {
    return new Snake();
}

CRAWL::IAI *World::initBackGroundAI() const {
    return IWorld::initBackGroundAI();
}

QString World::itemTextId() const {
    return "JungleLevel";
}

int World::requiredTier() const {
    return 0;
}

void World::handleXViewChanged(double dx) {
    auto eilorRotation = cameraRotation().toEulerAngles();
    eilorRotation.setX(eilorRotation.x() + dx);
    setCameraRotation(QQuaternion::fromEulerAngles(eilorRotation));
}

void World::handleYViewChanged(double dy) {
    auto eilorRotation = cameraRotation().toEulerAngles();
    eilorRotation.setY(eilorRotation.y() + dy );
    setCameraRotation(QQuaternion::fromEulerAngles(eilorRotation));
}

}
