//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#



#ifndef EXAMPLE_TEST_H
#define EXAMPLE_TEST_H
#include "test.h"
#include "testutils.h"

#include <QtTest>

class PluginLoaderTest: public Test, protected TestUtils
{
public:
    PluginLoaderTest();
    ~PluginLoaderTest();

    void test();

};

#endif // EXAMPLE_TEST_H
