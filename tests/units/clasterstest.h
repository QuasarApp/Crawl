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
    void test() override;
private:

    /**
     * @brief testOneClaster This test check functionality of the claster class.
     */
    void testOneClaster() const;

    /**
     * @brief testClastersWithWorld This test check clasters integrarion on the world
     */
    void testClastersWithWorld() const;
};

#endif // CLASTERSTEST_H
