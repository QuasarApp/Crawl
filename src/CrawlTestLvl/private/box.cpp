//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "box.h"

#include <QColor>

namespace TestLvl {

Box::Box(): IWorldItem("Box") {
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
}

void Box::onIntersects(const IWorldItem *item) {
    Q_UNUSED(item);
}
}
