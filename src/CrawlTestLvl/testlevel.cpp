//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "testlevel.h"
#include "world.h"
#include "nest.h"
#include "testsnake.h"

TestLevel::TestLevel() {
    initTestLvlResources();
    setWorld(new TestLvl::World());
    setPreviewScane(new TestLvl::Nest());

    addItem(new TestLvl::TestSnake());

}
