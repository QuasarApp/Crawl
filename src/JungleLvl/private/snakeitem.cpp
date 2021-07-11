//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "snakeitem.h"

namespace JungleLvl {

SnakeItem::SnakeItem(): CRAWL::SnakeItem("JungleSnakeItem") {
    setMash("qrc:/mesh/meshes/Other/Snake_body.mesh");
    setBaseColorMap("qrc:/mesh/meshes/Other/Snake_Base.jpg");
    setSize({1.5,1.5,1.5});
}

void SnakeItem::init() {

}

void SnakeItem::onIntersects(const IWorldItem *) {

}

}
