//#
//# Copyright (C) 2020-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#s

#include "test.h"
#include "testutils.h"

#ifndef CLASTERSTEST_H
#define CLASTERSTEST_H

/**
 * @brief The ClastersTest class This test of the claster objects system.
 */
class ClastersTest: public Test, protected TestUtils
{
public:
    ClastersTest();

    // Test interface
public:
    void test() override;
};

#endif // CLASTERSTEST_H
