//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "plate.h"

namespace TestLvl {


Plate::Plate(): CRAWL::GroundTile("TestPlate")
{
    setMash("#Cube");
    setColor("#5c4f45");
    setSize({10,10,0.01});
    setZ(0);
}

void Plate::render(unsigned int){

}
}
