//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef DAYITEM_H
#define DAYITEM_H

#include "iworldlight.h"
#include "Extensions/circularmotion.h"
namespace CRAWL {

/**
 * @brief The DayItem class This is base class of the sun of moon of anther movable around center objects.
 */
class DayItem: public IWorldLight, public CircularMotion {
    Q_OBJECT
public:
    DayItem(const QVector3D* center,
            const QString& name,
            const QString& viewTempalte = "qrc:/CrawlModule/Light.qml",
            QObject *ptr = nullptr);

    void render(unsigned int tbfMsec);
};
}
#endif // DAYITEM_H
