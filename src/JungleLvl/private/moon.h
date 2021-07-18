//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef MOON_H
#define MOON_H

#include "Crawl/dayitem.h"


namespace JungleLvl {

class Moon: public CRAWL::DayItem {
    Q_OBJECT
public:
    Moon(const QVector3D *center);

    void init();

    // IWorldItem interface
protected:
    void onIntersects(const IWorldItem *item);
};
}
#endif // MOON_H
