//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "stone.h"

namespace JungleLvl {


Stone::Stone(): CRAWL::IWorldItem(AUTO_CLASS_NAME)
{
    QStringList mashes {
        "qrc:/mesh/meshes/Stone/Stone_1.mesh",
        "qrc:/mesh/meshes/Stone/Stone_2.mesh",
        "qrc:/mesh/meshes/Stone/Stone_3.mesh",

    };

    setMash(mashes[rand() % mashes.size()]);

    setBaseColorMap("qrc:/mesh/meshes/Stone/Stone_Base.jpg");
    setNormalMap("qrc:/mesh/meshes/Stone/Stone_Normal.jpg");

    setSize({1,1,1});
    setRatation(QQuaternion::fromEulerAngles({0,0, static_cast<float>(rand() % 360)}));
}

void Stone::onIntersects(const IWorldItem *) {

}

}
