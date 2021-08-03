//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "rotationaroundaxis.h"

#include <Crawl/guiobject.h>

namespace CRAWL {

RotationAroundAxis::RotationAroundAxis(): CircularMotion(nullptr) {

}

void RotationAroundAxis::renderRotation(GuiObject *object, unsigned int tbfMsec) {
    setAnglePosition(anglePosition() + angularVelocity() * (tbfMsec / 1000.0f));

    object->setRotation(QQuaternion::fromAxisAndAngle(axis(), angularVelocity()));
}

void RotationAroundAxis::renderPosition(GuiObject *, unsigned int ) {

}

}
