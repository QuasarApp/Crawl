//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef ABSLVLSNAKEITEM_H
#define ABSLVLSNAKEITEM_H

#include "Crawl/snakeitem.h"

class AbsLvlSnakeItem: public SnakeItem {

    Q_OBJECT

public:
    AbsLvlSnakeItem();

    // IWorldItem interface
protected:
    void onIntersects(const IWorldItem *item) override;
};

#endif // ABSLVLSNAKEITEM_H
