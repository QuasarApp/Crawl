//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "testsnake.h"
#include <testsnakeitem.h>

TestSnake::TestSnake(): Snake("Snake") {
    setBreakingForce(50);
    setAngularVelocity(100);
    setColor("#90faaa");
    setMash("qrc:/mesh/res/meshes/cube.mesh");
    setSize({2,1,1});

    registerBodyitem<TestSnakeItem>();

}

void TestSnake::onIntersects(const IWorldItem *item) {
    Q_UNUSED(item);

}
