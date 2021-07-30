//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "basemotion.h"
#include "Crawl/guiobject.h"

namespace CRAWL {

BaseMotion::BaseMotion() {

}

const QQuaternion &BaseMotion::staticRotation() const {
    return _staticRotation;
}

void BaseMotion::setStaticRotation(const QQuaternion &newStaticRotation) {
    _staticRotation = newStaticRotation;
}

void BaseMotion::render(unsigned int tbfMsec) {
    if (auto _this = checkminimumRequariedType<GuiObject>()) {
        renderPosition(_this, tbfMsec);
        renderRotation(_this, tbfMsec);
    }
}
}
