//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "affector.h"

namespace CRAWL {

Affector::Affector(const QString &name,
                   const QString &viewTempalte,
                   QObject *ptr) :
    IWorldItem(name, viewTempalte, ptr)
{

}

bool Affector::enabled() const {
    return _enabled;
}

void Affector::setEnabled(bool newEnabled) {
    if (_enabled == newEnabled)
        return;
    _enabled = newEnabled;
    emit enabledChanged();
}

}
