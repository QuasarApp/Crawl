//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "defaultcontrol.h"
#include "playableobject.h"

namespace CRAWL {


PlayableObject::PlayableObject(const QString &name,
                 const QString &viewTempalte,
                 QObject *ptr):
    IWorldItem(name, viewTempalte, ptr) {

    setFDecorative(false);
}

void PlayableObject::render(unsigned int tbfMsec) {
    MovableObject::render(tbfMsec);
}

void PlayableObject::setControl(const IControl *control) {


    if (auto oldControl = dynamic_cast<const DefaultControl*>(_currentControl)) {
        disconnect(oldControl, &DefaultControl::userTap, this, &PlayableObject::onTap);
    }

    auto defaultControl = dynamic_cast<const DefaultControl*>(control);
    _currentControl = defaultControl;

    if (_currentControl) {
        connect(defaultControl, &DefaultControl::userTap, this, &PlayableObject::onTap);
    }
}

}
