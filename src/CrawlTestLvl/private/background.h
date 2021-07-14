//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Crawl/groundclaster.h"

namespace TestLvl {

/**
 * @brief The Background class
 */
class Background: public CRAWL::GroundClaster
{
public:
    Background();

    // IWorldItem interface
protected:
    void onIntersects(const IWorldItem *item) override;

    // AutoGenerateClaster interface
public:
    unsigned int itemsCount() const override;
};

}
#endif // BACKGROUND_H
