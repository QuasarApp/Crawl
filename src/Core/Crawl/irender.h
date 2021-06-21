//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef IRENDER_H
#define IRENDER_H

#include "global.h"

/**
 * @brief The IRender class This interface provide render functionality for all objects.
 * @note Override the render method.
 */
class CRAWL_EXPORT IRender {
public:
    IRender();
    virtual ~IRender() = default;

    /**
     * @brief render This method should be recalc all properyes of the this object.
     * @param tbf This is time betwin frame in milesecunds.
     */
    virtual void render(unsigned int tbfMsec) = 0;
};

#endif // IRENDER_H
