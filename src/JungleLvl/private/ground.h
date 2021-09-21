//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef GROUND_H
#define GROUND_H

#include "Crawl/groundclaster.h"

namespace JungleLvl {


/**
 * @brief The Ground class This is main ground plate
 */
class Ground : public CRAWL::GroundClaster
{
public:
    Ground();
    unsigned int itemsCount() const override;

    // GroundClaster interface
protected:
    int newObjectDistance() const;
};

}
#endif // GROUND_H
