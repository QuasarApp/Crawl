//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef IGROUND_H
#define IGROUND_H

#include "iworlditem.h"
#include "global.h"

/**
 * @brief The IGround class This is one tile of the world. Any objects of this type created automatically for filing ground plain.
 */
class SNAKEPROJECT_EXPORT IGround: public IWorldItem {
public:
    IGround();

    // IRender interface
public:
    void render(unsigned int tbfMsec) override;
};

#endif // IGROUND_H
