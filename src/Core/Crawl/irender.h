#ifndef IRENDER_H
#define IRENDER_H

#include "global.h"

/**
 * @brief The IRender class This interface provide render functionality for all objects.
 * @note Override the render method.
 */
class Crawl_EXPORT IRender {
public:
    IRender();

    /**
     * @brief render This method should be recalc all properyes of the this object.
     * @param tbf This is time betwin frame in milesecunds.
     */
    virtual void render(unsigned int tbfMsec) = 0;
};

#endif // IRENDER_H
