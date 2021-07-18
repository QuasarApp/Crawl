//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "wood.h"

namespace JungleLvl {

Wood::Wood(): CRAWL::IWorldItem(AUTO_CLASS_NAME) {
    QStringList mashes {
        "qrc:/mesh/meshes/Wood/Wood_1.mesh",
        "qrc:/mesh/meshes/Wood/Wood_2.mesh",
        "qrc:/mesh/meshes/Wood/Wood_3.mesh",
        "qrc:/mesh/meshes/Wood/Wood_4.mesh",
        "qrc:/mesh/meshes/Wood/Wood_5.mesh",
        "qrc:/mesh/meshes/Wood/Wood_6.mesh",
        "qrc:/mesh/meshes/Wood/Wood_7.mesh",
        "qrc:/mesh/meshes/Wood/Wood_8.mesh",

    };

    setMash(mashes[rand() % mashes.size()]);

    setBaseColorMap("qrc:/mesh/meshes/Wood/Wood_Base.jpg");
    setNormalMap("qrc:/mesh/meshes/Wood/Wood_Normal.jpg");
    setRoughnessMap("qrc:/mesh/meshes/Wood/Wood_Roughness.jpg");
    setSize({1,1,1});
    setRatation(QQuaternion::fromEulerAngles({0,0, static_cast<float>(rand() % 360)}));
}

void Wood::onIntersects(const IWorldItem *) {

}
}
