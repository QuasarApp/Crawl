//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef GROUPOBJBOXITEM_H
#define GROUPOBJBOXITEM_H

#include "box.h"
#include "Crawl/clasteritem.h"

namespace TestLvl {

class GroupObjboxItem: public CRAWL::ClasterItem, public Box {

public:
    GroupObjboxItem();

    // IRender interface
public:
    void init();
    void render(unsigned int tbfMsec);
};

}

#endif // GROUPOBJBOXITEM_H
