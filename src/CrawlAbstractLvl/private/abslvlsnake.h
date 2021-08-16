//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef ABSLVLSNAKE_H
#define ABSLVLSNAKE_H

#include "Crawl/snake.h"

namespace AbstractLvl {

class AbsLvlSnake : public CRAWL::Snake {

    Q_OBJECT

public:
    AbsLvlSnake();


    // IItem interface
public:
    QString itemTextId() const override;
    QString itemName() const override;
    QString description() const override;
    QString image() const override;
    int cost() const override;
    int requiredTier() const override;
};

}

#endif // ABSLVLSNAKE_H
