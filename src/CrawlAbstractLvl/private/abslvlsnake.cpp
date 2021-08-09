//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "abslvlsnake.h"
#include "abslvlsnakeitem.h"

namespace AbstractLvl {

AbsLvlSnake::AbsLvlSnake(): Snake(AUTO_CLASS_NAME) {
    setBreakingForce(50);
    setAngularVelocity(100);
    setColor("#90faaa");
    setMash("qrc:/mesh/meshes/SnakePatternHead.mesh");
    setStaticRotation(QQuaternion::fromEulerAngles(0,0,90));
    setSize({1,1,1});

    setScales({{0, 0.9},
              {0.6, 1},
              {1, 0.5}});

    setLengthBetwinItemsMap({{0, 3},
                             {0.001, 0.9},
                             {0.6, 1},
                             {1, 0.5}});

    registerItemType<AbsLvlSnakeItem>();
}


}
