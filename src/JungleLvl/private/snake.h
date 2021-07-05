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

/**
 * @brief The Snake class this is main player class of the jungle level
 */
class CRAWL_JUNGLE_LEVEL_EXPORT Snake: public CRAWL::Snake
{
    Q_OBJECT

public:
    Snake();

    // IWorldItem interface
protected:
    void onIntersects(const IWorldItem *) override;
};

#endif // SNAKE_H
