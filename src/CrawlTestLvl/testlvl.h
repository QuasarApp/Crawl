//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef TESTLVL_H
#define TESTLVL_H

#include <Crawl/ilevel.h>
#include "testlevel_global.h"

inline void initTestLvlResources() { Q_INIT_RESOURCE(Empty);
                                     Q_INIT_RESOURCE(testLvl);}
/**
 * @brief The TestLvl class This is test lvlv wraper of the crawl
 */
class CRAWL_TEST_LEVEL_EXPORT TestLvl: public ILevel
{
public:
    TestLvl();

    // ILevel interface
public:
    IWorld *world() override;
};

#endif // TESTLVL_H
