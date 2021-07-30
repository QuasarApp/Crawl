//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef ABSLVLCONTROL_H
#define ABSLVLCONTROL_H
#include "Crawl/defaultcontrol.h"

namespace AbstractLvl {

/**
 * @brief The AbsLvlControl class This controll support custom camera-rotation functions.
 */
class AbsLvlControl: public CRAWL::DefaultControl
{
    Q_OBJECT
public:
    AbsLvlControl();
    QString initQmlView() const override;

};

}

#endif // ABSLVLCONTROL_H
