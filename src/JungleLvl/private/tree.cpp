//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "tree.h"
namespace JungleLvl {

Tree::Tree(): CRAWL::IWorldItem(AUTO_CLASS_NAME) {

    QStringList mashes {
        "qrc:/mesh/meshes/Plant/Tree_1.mesh",
        "qrc:/mesh/meshes/Plant/Tree_2.mesh",
        "qrc:/mesh/meshes/Plant/Tree_3.mesh",
        "qrc:/mesh/meshes/Plant/Tree_4.mesh",
        "qrc:/mesh/meshes/Plant/Tree_5.mesh",
        "qrc:/mesh/meshes/Plant/Tree_6.mesh",

    };

    setMash(mashes[rand() % mashes.size()]);
    setBaseColorMap("qrc:/mesh/meshes/Plant/Tree_Base.jpg");
    setSize({1,1,1});
    setRotation(QQuaternion::fromEulerAngles({static_cast<float>(rand() % 60 - 30),
                                              static_cast<float>(rand() % 60 - 30),
                                              static_cast<float>(rand() % 360)}));

    if (rand() % 2)
        setZ(-static_cast<float>(rand() % 10));
}

void Tree::onIntersects(const IWorldItem *) {

}
}
