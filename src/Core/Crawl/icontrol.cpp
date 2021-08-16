//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "icontrol.h"

namespace CRAWL {


IControl::IControl() {

}

IControl::~IControl() {

}

const QString &IControl::view() {
    if (_view.isEmpty()) {
        setView(initQmlView());
    }

    return _view;
}

void IControl::setView(const QString &newView) {
    if (_view == newView)
        return;
    _view = newView;
    emit viewChanged();
}

}
