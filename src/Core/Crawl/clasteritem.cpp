//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "Extensions/claster.h"
#include "clasteritem.h"

ClasterItem::ClasterItem(const QString &name,
                         const QString &viewTempalte,
                         QObject *ptr):
    IWorldItem(name, viewTempalte, ptr) {

}

ClasterItem::~ClasterItem() {
    for (auto claster : qAsConst(_parentClasters)) {
        claster->remove(this);
    }
}

int ClasterItem::parentClastersCount() const {
    return _parentClasters.size();
}

void ClasterItem::setClaster(Claster *claster) {
    _parentClasters += claster;
}

void ClasterItem::removeClaster(Claster *claster) {
    _parentClasters -= claster;
}

const QSet<Claster *> &ClasterItem::parentClasters() const {
    return _parentClasters;
}
