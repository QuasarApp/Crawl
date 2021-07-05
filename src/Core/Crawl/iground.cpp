//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "iground.h"
#include "iworld.h"

namespace CRAWL {


IGround::IGround(const QString &name,
                 const QString &viewTempalte,
                 QObject *ptr):
    IWorldItem(name, viewTempalte, ptr) {

}

void IGround::render(unsigned int ) {
    const IWorldItem *playerObject = getPlayer();
    QVector3D camera = world()->cameraReleativePosition();

    if (playerObject->position().x() - position().x() >
            camera.z() * 2) {
        setX(playerObject->position().x() + camera.z() * 4);
    }
}

}
