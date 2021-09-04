//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef CONTROLPOS_H
#define CONTROLPOS_H

#include <Crawl/groupobject.h>


namespace CRAWL {

/**
 * @brief The ControlPos class
 */
class ControlPos: public GroupObject {
public:
    ControlPos();

// Claster interface
public:
    void add(ClasterItem *object);
    void remove(ClasterItem *object);

private:

    /**
     * @brief The _Figure enum
     */
    enum _Figure {
        CIRCLE,
        SQUARE,
        LINE
    };

    /**
     * @brief changeLayout
     * @param fig
     */
    void changeLayout(const _Figure &fig);

};

}
#endif // CONTROLPOS_H
