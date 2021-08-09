//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "testsnake.h"
#include <testsnakeitem.h>

namespace TestLvl {

TestSnake::TestSnake(): Snake("Snake") {
    setBreakingForce(50);
    setAngularVelocity(100);
    setColor("#90faaa");
    setMash("qrc:/mesh/meshes/cube.mesh");
    setSize({2,1,1});

    registerItemType<TestSnakeItem>();
    setContainerSize({2, 2, 2});

}

unsigned int TestSnake::itemsCount() const {
    return 50;
}
}
