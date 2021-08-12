//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "background.h"
#include "box.h"
#include "plate.h"
#include "testcontrol.h"
#include "world.h"
#include <testsnake.h>
#include "Crawl/iworlditem.h"
#include <Crawl/day.h>
#include <Crawl/defaultlight.h>
#include <Crawl/dynamicwint.h>
#include <Crawl/fire.h>
#include <Crawl/moon.h>
#include <Crawl/sun.h>

namespace TestLvl {


World::World() {
    setCameraReleativePosition({50,0,100});
    setCameraRotation(QQuaternion::fromEulerAngles({0,0,0}));
}

CRAWL::WorldRule *World::initWorldRules() {
    using Day = CRAWL::Day<CRAWL::Sun, CRAWL::Moon>;

    return new CRAWL::WorldRule {
        {0, {{registerObject<Box>(), 1000},
             {registerObject<CRAWL::Fire>(), 10},
             {registerObject<CRAWL::DynamicWint>(), 1},

             {registerObject<Background>(), 1},
             {registerObject<Day>(), 1}}}
    };
}

QString World::initHdrBackGround() const {
    return "qrc:/hdr/hdr/testHDR.hdr";
}

QString World::description() const {
    return "This a test lvl";
}

QString World::image() const {
    return "qrc:/hdr/hdr/testHDR.jpg";
}

QString World::itemName() const {
    return "Test";
}

int World::cost() const {
    return 0;
}

CRAWL::IControl *World::initUserInterface() const {
    return new TestControl();
}

void World::initControl(CRAWL::IControl *control) {
    if (auto test = dynamic_cast<TestControl*>(control)) {
        connect(test, &TestControl::xChanged, this, &World::handleXViewChanged);
        connect(test, &TestControl::yChanged, this, &World::handleYViewChanged);
    }

    return IWorld::initControl(control);
}

CRAWL::PlayableObject *World::initPlayer() const {
    return new TestSnake();
}

CRAWL::IAI *World::initBackGroundAI() const {
    return IWorld::initBackGroundAI();
}

QString World::itemTextId() const {
    return "TestLevel";
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
