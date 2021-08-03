//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef ROTATIONAROUNDAXIS_H
#define ROTATIONAROUNDAXIS_H

#include "circularmotion.h"

namespace CRAWL {

/**
 * @brief The RotationAroundAxis class This class provide the rotation of our axis
 */
class RotationAroundAxis: public CircularMotion
{
public:
    RotationAroundAxis();

    // BaseMotion interface
protected:
    void renderRotation(GuiObject *object, unsigned int tbfMsec) override;
    void renderPosition(GuiObject *object, unsigned int tbfMsec) override;

};

}



#endif // ROTATIONAROUNDAXIS_H
