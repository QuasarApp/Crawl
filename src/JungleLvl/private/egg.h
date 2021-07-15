//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef EGG_H
#define EGG_H


#include <Crawl/iworlditem.h>
#include <jungle_global.h>


namespace JungleLvl {


class CRAWL_JUNGLE_LEVEL_EXPORT Egg: public CRAWL::IWorldItem
{
    Q_OBJECT
public:
    Egg(const QString name);
    void onIntersects(const IWorldItem *);

};

}
#endif // EGG_H
