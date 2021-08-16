//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef PLATE_H
#define PLATE_H
#include "Crawl/groundtile.h"
namespace TestLvl {


/**
 * @brief The Plate class
 */
class Plate: public CRAWL::GroundTile {
    Q_OBJECT
public:
    Plate();

    // IRender interface
public:
    void render(unsigned int tbfMsec) override;
};
}
#endif // PLATE_H
