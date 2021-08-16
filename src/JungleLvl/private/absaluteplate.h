#ifndef ABSALUTEPLATE_H
#define ABSALUTEPLATE_H

#include "Crawl/iworlditem.h"

namespace JungleLvl {

class AbsalutePlate : public CRAWL::IWorldItem
{
    Q_OBJECT
public:
    AbsalutePlate();

    // IRender interface
public:
    void render(unsigned int tbfMsec) override;
};

}
#endif // ABSALUTEPLATE_H
