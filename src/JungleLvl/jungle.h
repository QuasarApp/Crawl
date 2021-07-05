//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef JUNGLE_H
#define JUNGLE_H

#include "jungle_global.h"
#include <Crawl/ilevel.h>

inline void initTestLvlResources() { Q_INIT_RESOURCE(jungle);
                                     Q_INIT_RESOURCE(jungleLvl);}

/**
 * @brief The Jungle class This is main class of the jungle lvl
 */
class CRAWL_JUNGLE_LEVEL_EXPORT Jungle: public ILevel
{
public:
    Jungle();

    // ILevel interface
public:
    IWorld *world() override;
};

#endif // JUNGLE_H
