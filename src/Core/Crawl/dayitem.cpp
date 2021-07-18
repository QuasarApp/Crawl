//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "dayitem.h"

namespace CRAWL {

DayItem::DayItem(
        const QVector3D* center,
        const QString &name,
        const QString &viewTempalte,
        QObject *ptr):

    IWorldLight(name, viewTempalte, ptr),
    CircularMotion(center) {


}

void DayItem::render(unsigned int tbfMsec) {
    CircularMotion::render(tbfMsec);
    setVisible(position().z() > 0);

}
}
