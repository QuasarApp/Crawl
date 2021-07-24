//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef ABSTRACTLEVEL_H
#define ABSTRACTLEVEL_H

#include <Crawl/ilevel.h>
#include "abstractlvl_global.h"

inline void initAbstractLvlResources() { Q_INIT_RESOURCE(abstractLevel);
                                         Q_INIT_RESOURCE(absLvlRes);}
/**
 * @brief The AbstractLvl class This is test lvlv wraper of the crawl
 */
class CRAWL_ABSTRACT_LEVEL_EXPORT AbstractLevel: public CRAWL::ILevel {
public:
    AbstractLevel();

    // ILevel interface
public:
    CRAWL::IWorld *world() override;
};

#endif // ABSTRACTLEVEL_H
