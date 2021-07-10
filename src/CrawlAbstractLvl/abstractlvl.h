//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef ABSTRACTLVL_H
#define ABSTRACTLVL_H

#include <Crawl/ilevel.h>
#include "abstractlvl_global.h"

inline void initAbstractLvlResources() { Q_INIT_RESOURCE(AbstractLvl);
                                         Q_INIT_RESOURCE(absLvlRes);}
/**
 * @brief The AbstractLvl class This is test lvlv wraper of the crawl
 */
class CRAWL_ABSTRACT_LEVEL_EXPORT AbstractLvl: public CRAWL::ILevel {
public:
    AbstractLvl();

    // ILevel interface
public:
    CRAWL::IWorld *world() override;
};

#endif // ABSTRACTLVL_H
