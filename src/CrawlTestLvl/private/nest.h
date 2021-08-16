//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#
#ifndef NEST_H
#define NEST_H

#include "Crawl/ipreviewscaneworld.h"

namespace TestLvl {

/**
 * @brief The Nest class Test nest world.
 */
class Nest: public CRAWL::IPreviewScaneWorld
{
public:
    Nest(IWorld* mainWorld);

    // IWorld interface
public:
    CRAWL::WorldRule *initWorldRules() override;
    QString initHdrBackGround() const override;


protected:
    CRAWL::IWorldItem *generate(const QString &objectType) const override;
};

}
#endif // NEST_H
