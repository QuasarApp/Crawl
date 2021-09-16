//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef GROUPOBJBOX_H
#define GROUPOBJBOX_H

#include "Crawl/controlpos.h"
#include "Crawl/iworlditem.h"

namespace TestLvl {

class GroupObjBox: public CRAWL::ControlPos, public CRAWL::IWorldItem {
public:
    GroupObjBox();


    // IRender interface
public:
    void render(unsigned int tbfMsec);
    void init();
};

}
#endif // GROUPOBJBOX_H
