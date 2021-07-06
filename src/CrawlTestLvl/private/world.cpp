//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "box.h"
#include "plate.h"
#include "testcontrol.h"
#include "world.h"
#include <testsnake.h>
#include "Crawl/iworlditem.h"

namespace TestLvl {


World::World() {
    setCameraReleativePosition({0,0,100});
    setCameraRatation(QQuaternion::fromEulerAngles({0,0,-90}));
}

CRAWL::WorldRule *World::initWorldRules() {
    return new CRAWL::WorldRule {
        {0, {{registerObject<Box>(), 1000}}}
    };
}

QString World::initHdrBackGround() const {
    return "qrc:/hdr/hdr/testHDR.hdr";
}

QString World::description() const {
    return "This a test lvl";
}

QString World::imagePreview() const {
    return "qrc:/hdr/hdr/testHDR.jpg";
}

QString World::name() const {
    return "Test";
}

int World::costToUnlock() const {
    return 0;
}

CRAWL::IControl *World::initUserInterface() const {
    return new TestControl();
}

void World::initPlayerControl(CRAWL::IControl *control) {
    if (auto test = dynamic_cast<TestControl*>(control)) {
        connect(test, &TestControl::xChanged, this, &World::handleXViewChanged);
        connect(test, &TestControl::yChanged, this, &World::handleYViewChanged);
    }

    return IWorld::initPlayerControl(control);
}

CRAWL::IPlayer *World::initPlayer() const {
    return new TestSnake();
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
