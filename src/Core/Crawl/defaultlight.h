//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef DEFAULTLIGHT_H
#define DEFAULTLIGHT_H

#include "iworldlight.h"

namespace CRAWL {

/**
 * @brief The DefaultLight class This is default implementation of the world light.
 * This object create uniform illumination for all world.
 * For integration This object yo worl see the IWorld::initWorldRules method
 */
class DefaultLight final:  public IWorldLight
{
    Q_OBJECT
public:
    DefaultLight();

    void render(unsigned int tbfMsec) override;
    void init() override;
};

}
#endif // DEFAULTLIGHT_H
