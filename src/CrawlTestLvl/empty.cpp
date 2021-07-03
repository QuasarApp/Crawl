//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "Crawl/iworld.h"
#include "world.h"

inline void initResources() { Q_INIT_RESOURCE(Empty); }

extern "C" IWorld* worldInstance() {
    initResources();
    return new World();
}
