//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "Crawl/snakeitem.h"

#ifndef JUNGLESNAKEITEM_H
#define JUNGLESNAKEITEM_H

namespace JungleLvl {


class SnakeItem : public CRAWL::SnakeItem
{
public:
    SnakeItem();
    void init() override;
};

}
#endif // JUNGLESNAKEITEM_H
