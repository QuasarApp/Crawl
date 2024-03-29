//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "box.h"
#include "Crawl/iworld.h"
#include <QColor>

namespace TestLvl {

Box::Box(): ClasterItem("Box") {
    setMash("qrc:/mesh/meshes/cube.mesh");
    setSize({2,2,2});
    setColor(QColor::fromRgb(rand()).name());

    setRotation(QQuaternion::fromEulerAngles(
                    rand() % 360 ,
                    rand() % 360,
                    rand() % 360));

    setposition({static_cast<float>(rand() % 100) - 50,
                 static_cast<float>(rand() % 100) - 50,
                 0 });

    setFDecorative(false);

    setContainerSize({4, 4, 4});
}

void Box::action(IWorldItem *item) {
    if (item->className() == getPlayer()->className()) {
        respawn();
    }
}

void Box::firstSpawn() {
    float dX = rand() % static_cast<int>(world()->cameraReleativePosition().z());
    setX(dX);

    float dY = rand() % static_cast<int>(world()->cameraReleativePosition().z());
    setY(dY);
}

}
