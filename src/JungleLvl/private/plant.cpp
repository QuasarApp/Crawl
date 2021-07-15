//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "plant.h"
namespace JungleLvl {

Plant::Plant(): CRAWL::IWorldItem(AUTO_CLASS_NAME) {
    QStringList mashes {
        "qrc:/mesh/meshes/Plant/Plant_1.mesh",
        "qrc:/mesh/meshes/Plant/Plant_2.mesh"

    };

    setMash(mashes[rand() % mashes.size()]);

    setBaseColorMap("qrc:/mesh/meshes/Plant/Plant_Base.jpg");
    setSize({1,1,1});
    setRatation(QQuaternion::fromEulerAngles({0,0, static_cast<float>(rand() % 360)}));
}

void Plant::onIntersects(const IWorldItem *) {

}
}
