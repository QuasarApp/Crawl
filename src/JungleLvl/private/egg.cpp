//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "egg.h"
namespace JungleLvl {

Egg::Egg(const QString name): CRAWL::IWorldItem(name)
{
    QStringList mashes {
        "qrc:/mesh/meshes/Other/Egg.mesh",
    };

    setMash(mashes[rand() % mashes.size()]);

    setSize({1,1,1});
    setRotation(QQuaternion::fromEulerAngles({0,0, static_cast<float>(rand() % 360)}));
}

void Egg::onIntersects(const IWorldItem *) {

}

}
