//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "abslvlsnakeitem.h"

namespace AbstractLvl {

AbsLvlSnakeItem::AbsLvlSnakeItem():CRAWL::SnakeItem(AUTO_CLASS_NAME) {
    setMash("qrc:/mesh/meshes/SnakePatternBody.mesh");
    setColor("#20aa9a");
    setSize({1,1,1});
}

}
