//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "test.h"
#include "testutils.h"


#ifndef GROUPOBJECTTEST_H
#define GROUPOBJECTTEST_H

/**
 * @brief The GroupObjectTest class will be tests the CRAWL::GroupObject class from the core library.
 */
class GroupObjectTest: public Test, protected TestUtils
{
public:
    GroupObjectTest();
    void test();

private:
    /**
     * @brief testBehavior This method check the install objects on the main object.
     */
    void testBehavior() const;
};

#endif // GROUPOBJECTTEST_H
