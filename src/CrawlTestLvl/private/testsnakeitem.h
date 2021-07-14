//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef TESTSNAKEITEM_H
#define TESTSNAKEITEM_H

#include "Crawl/snakeitem.h"

namespace TestLvl {


class TestSnakeItem: public CRAWL::SnakeItem
{
    Q_OBJECT
public:
    TestSnakeItem();

    // IWorldItem interface
protected:
    void onIntersects(const IWorldItem *item) override;
};

}
#endif // TESTSNAKEITEM_H
