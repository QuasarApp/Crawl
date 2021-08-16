//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include <Crawl/snake.h>
#include "jungle_global.h"

#ifndef SNAKE_H
#define SNAKE_H

namespace JungleLvl {


/**
 * @brief The Snake class this is main player class of the jungle level
 */
class Snake: public CRAWL::Snake
{
    Q_OBJECT

public:
    Snake();
    QString itemTextId() const override;
    QString itemName() const override;
    QString description() const override;
    QString image() const override;
    int cost() const override;
    int requiredTier() const override;
    // IWorldItem interface
protected:
    unsigned int itemsCount() const override;


};


}
#endif // SNAKE_H
