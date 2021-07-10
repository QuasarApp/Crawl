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
    registerItemType<JungleLvl::SnakeItem>();
    setMash("qrc:/mesh/meshes/Other/Snake_head.mesh");
    setBaseColorMap("qrc:/mesh/meshes/Other/Snake_Base.jpg");
    setSize({1.5,1.5,1.5});
    setStaticRotation(QQuaternion::fromEulerAngles(0,90,-90));

}

void Snake::onIntersects(const IWorldItem *) {

}
}
