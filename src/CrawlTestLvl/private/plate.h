//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef PLATE_H
#define PLATE_H
#include "Crawl/iground.h"

class Plate: public CRAWL::IGround {
public:
    Plate();

    // IWorldItem interface
protected:
    void onIntersects(const IWorldItem *item) override;
};

#endif // PLATE_H
