//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "boxitem.h"
#include "groupobjbox.h"

namespace TestLvl {

GroupObjBox::GroupObjBox(): CRAWL::IWorldItem("GroupObjBox") {

    setDistance(20);
    changeLayout(CRAWL::LayoutType::CIRCLE);

    for(int i(0); i < 20; i++)   {
        add(new BoxItem);
    }

}

void GroupObjBox::render(unsigned int tbfMsec)
{
    Layout::render(tbfMsec);
    IWorldItem::render(tbfMsec);
}

void GroupObjBox::init()
{

}




}
