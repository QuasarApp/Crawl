//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef IRENDER_H
#define IRENDER_H

#include "global.h"
#include "quasarapp.h"

/**
 * @brief The IRender class This interface provide render functionality for all objects.
 * @note Override the render method.
 * @note The  IRender Interface suppor extension concept
 *
 * ### Extension concept
 * You can create child class of the IRender class and override the render method. But the render method will works with another class object using dynamic_cast of this pointer.
 *
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

    /**
     * @brief checkminimumRequariedType This method check
     * @return This object casted to Requared type this objct.
     *
     * **Example of use**:
     *
     * ```cpp
     * auto _this = checkminimumRequariedType<RequaredType>();
     * ```
     */
    template<class Requared>
    Requared* checkminimumRequariedType() {

        Requared* result = dynamic_cast<Requared*>(this);

        debug_assert(result, "This render function not support this class");

        return result;
    };
};

#endif // IRENDER_H
