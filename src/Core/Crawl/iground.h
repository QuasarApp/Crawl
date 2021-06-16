#ifndef IGROUND_H
#define IGROUND_H

#include "iworlditem.h"
#include "global.h"

/**
 * @brief The IGround class This is one tile of the world. Any objects of this type created automatically for filing ground plain.
 */
class CRAWL_EXPORT IGround: public IWorldItem {
public:
    IGround();

    // IRender interface
public:
    void render(unsigned int tbfMsec) override;
};

#endif // IGROUND_H
