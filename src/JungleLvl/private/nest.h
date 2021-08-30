//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef NEST_H
#define NEST_H
#include <Crawl/ipreviewscaneworld.h>

namespace JungleLvl {

/**
 * @brief The Nest class
 */
class Nest:  public CRAWL::IPreviewScaneWorld
{
public:
    Nest();

    // IWorld interface
public:
    CRAWL::WorldRule *initWorldRules() override;
    QString initHdrBackGround() const override;
};

}
#endif // NEST_H
