//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "claster.h"
#include "singleclasterworlditem.h"
#include "quasarapp.h"

SingleClasterWorldItem::SingleClasterWorldItem(const QString &name,
                                               const QString &viewTempalte,
                                               QObject *ptr):
    ClasterItem(name, viewTempalte, ptr) {

}

void SingleClasterWorldItem::setClaster(Claster *claster) {
    if (parentClasters().size() > 0) {
        Claster* parent = *parentClasters().begin();
        parent->remove(this);
        removeClaster(parent);
    }

    ClasterItem::setClaster(claster);
}
