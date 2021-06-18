//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "claster.h"
#include "clasteritem.h"

ClasterItem::ClasterItem() {

}

ClasterItem::~ClasterItem() {
    if (parentClasters().size() && *parentClasters().begin()) {
        (*parentClasters().begin())->remove(this);
    }
}

void ClasterItem::setClaster(Claster *claster) {
    _parentClasters += claster;
}

const QSet<Claster *> &ClasterItem::parentClasters() const {
    return _parentClasters;
}
