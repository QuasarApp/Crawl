//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef BOX_H
#define BOX_H
#include "Crawl/iworlditem.h"

namespace TestLvl {


class Box: public CRAWL::IWorldItem {

public:
    Box();

    // IWorldItem interface
protected:
    void onIntersects(const IWorldItem *item) override;
};
}
#endif // BOX_H
