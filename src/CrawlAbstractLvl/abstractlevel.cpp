//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "abstractlevel.h"
#include "abslvlworld.h"

AbstractLevel::AbstractLevel() {

}

CRAWL::IWorld *AbstractLevel::world() {
    initAbstractLvlResources();
    return new AbstractLvl::AbsLvlWorld();
}
