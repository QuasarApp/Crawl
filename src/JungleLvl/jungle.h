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

inline void initJungleLvlResources() {   Q_INIT_RESOURCE(jungleHDR);
                                         Q_INIT_RESOURCE(jungleMash);
                                         Q_INIT_RESOURCE(jungleIntro);
                                         Q_INIT_RESOURCE(jungleSound);
                                         Q_INIT_RESOURCE(jungle);}

/**
 * @brief The Jungle class This is main class of the jungle lvl
 */
class CRAWL_JUNGLE_LEVEL_EXPORT Jungle: public CRAWL::ILevel
{
public:
    Jungle();

};

#endif // JUNGLE_H
