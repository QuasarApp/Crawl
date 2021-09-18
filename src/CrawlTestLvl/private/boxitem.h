//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef BOXITEM_H
#define BOXITEM_H

#include "box.h"

namespace TestLvl {

class BoxItem: public Box {
public:
    BoxItem();

    // IRender interface
public:
    void render(unsigned int tbfMsec);
};

}
#endif // BOXITEM_H
