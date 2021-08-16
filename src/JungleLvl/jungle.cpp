//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "jungle.h"
#include "world.h"
#include "nest.h"

Jungle::Jungle() {
    initJungleLvlResources();

    auto world = new JungleLvl::World();

    setWorld(world);

    setPreviewScane(new JungleLvl::Nest(world));
}
