//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "box.h"
#include "groupobjbox.h"

namespace TestLvl {

GroupObjBox::GroupObjBox(): CRAWL::ClasterItem("GroupObjBox") {

    setDistance(2);
    changeLayout(CRAWL::Refresh::CIRCLE);

    add(new Box);
    add(new Box);
    add(new Box);
    add(new Box);
    add(new Box);
    add(new Box);
    add(new Box);
    add(new Box);
    add(new Box);
    add(new Box);
    add(new Box);
    add(new Box);
    add(new Box);
    add(new Box);
    add(new Box);
    add(new Box);
    add(new Box);
    add(new Box);
    add(new Box);
    add(new Box);

}

void GroupObjBox::render(unsigned int tbfMsec)
{

}

void GroupObjBox::init()
{

}




}
