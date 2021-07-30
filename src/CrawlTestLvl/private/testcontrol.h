//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef TESTCONTROL_H
#define TESTCONTROL_H
#include "Crawl/defaultcontrol.h"

namespace TestLvl {

/**
 * @brief The TestControl class This controll support custom camera-rotation functions.
 */
class TestControl: public CRAWL::DefaultControl
{
    Q_OBJECT
public:
    TestControl();
    QString initQmlView() const override;

signals:
    void xChanged(double);
    void yChanged(double);
};

}

#endif // TESTCONTROL_H
