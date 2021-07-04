//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef TESTCONTROL_H
#define TESTCONTROL_H
#include "Crawl/defaultcontrol.h"

/**
 * @brief The TestControl class This controll support custom camera-ratation functions.
 */
class AbsLvlControl: public DefaultControl
{
    Q_OBJECT
public:
    AbsLvlControl();
    QString initQmlView() const override;

};

#endif // TESTCONTROL_H
