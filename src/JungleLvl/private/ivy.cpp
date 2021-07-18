//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "ivy.h"
namespace JungleLvl {

Ivy::Ivy(): CRAWL::IWorldItem(AUTO_CLASS_NAME) {
    QStringList mashes {
        "qrc:/mesh/meshes/Plant/ivy.mesh",

    };

    setMash(mashes[rand() % mashes.size()]);

    setBaseColorMap("qrc:/mesh/meshes/Plant/Ivy_Base.jpg");
    setSize({1,1,1});
    setRatation(QQuaternion::fromEulerAngles({0,0, static_cast<float>(rand() % 360)}));
}

void Ivy::onIntersects(const IWorldItem *) {

}
}
