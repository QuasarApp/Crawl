//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "snake.h"
#include "snakeitem.h"

namespace JungleLvl {

Snake::Snake(): CRAWL::Snake("JungleSnake") {
    setBreakingForce(50);
    setAngularVelocity(100);

    registerItemType<JungleLvl::SnakeItem>();
    setMash("qrc:/mesh/meshes/Other/Snake_head.mesh");
    setBaseColorMap("qrc:/mesh/meshes/Other/Snake_Base.jpg");
    setSize({1,1,1});
    setStaticRotation(QQuaternion::fromEulerAngles(0,0,0));


    setScales({{0, 0.9},
              {0.6, 1},
              {1, 0.5}});

    setLengthBetwinItemsMap({{0, 3},
                             {0.001, 0.9},
                             {0.6, 1},
                             {1, 0.5}});
}

void Snake::onIntersects(const IWorldItem *) {

}

unsigned int Snake::itemsCount() const {
    return 50;
}
}
