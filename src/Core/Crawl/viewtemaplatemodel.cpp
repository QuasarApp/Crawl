//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "viewtemaplatemodel.h"

namespace CRAWL {

ViewTemaplateModel::ViewTemaplateModel(const QString &viewTempalte, QObject *ptr): QObject(ptr) {
    _viewTemplate = viewTempalte;
}

const QString &ViewTemaplateModel::viewTemplate() const {
    return _viewTemplate;
}

}
