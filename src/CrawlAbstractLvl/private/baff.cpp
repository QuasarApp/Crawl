//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "baff.h"

namespace AbstractLvl {

Baff::Baff() : IWorldItem(AUTO_CLASS_NAME) {
    setMash("qrc:/mesh/meshes/Baff.mesh");
    setSize({1,1,1});
    setColor("#00ff00");
    setposition({200, 0, 200});
    setZ(0);
}


}
