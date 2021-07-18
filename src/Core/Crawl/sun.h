//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef SUN_H
#define SUN_H

#include "Crawl/dayitem.h"

namespace CRAWL {

/**
 * @brief The Sun class This is default implementation of the sun for the Day class.
 */
class CRAWL_EXPORT Sun: public DayItem
{
    Q_OBJECT
public:
    Sun(const QVector3D* center);

    // IWorldItem interface
protected:
    void onIntersects(const IWorldItem *item);

    // IRender interface
public:
    void init();
};

}
#endif // SUN_H
