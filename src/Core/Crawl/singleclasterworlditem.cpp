//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "claster.h"
#include "singleclasterworlditem.h"

SingleClasterWorldItem::SingleClasterWorldItem() {

}

void SingleClasterWorldItem::setClaster(Claster *claster) {
    if (_parentClaster) {
        _parentClaster->remove(guiId());
    }

    _parentClaster = claster;
}
