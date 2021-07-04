//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef OBJBAFF_H
#define OBJBAFF_H
#include "Crawl/iworlditem.h"


class Baff: public IWorldItem {
public:
    Baff();

    // IWorldItem interface
protected:
    void onIntersects(const IWorldItem *item) override;
};

#endif // OBJBAFF_H
