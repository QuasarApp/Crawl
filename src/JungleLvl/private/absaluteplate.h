#ifndef ABSALUTEPLATE_H
#define ABSALUTEPLATE_H

#include "Crawl/iworlditem.h"

namespace JungleLvl {

class AbsalutePlate : public CRAWL::IWorldItem
{
    Q_OBJECT
public:
    AbsalutePlate();

    // IWorldItem interface
protected:
    void onIntersects(const IWorldItem *item) override;

    // IRender interface
public:
    void render(unsigned int tbfMsec) override;
};

}
#endif // ABSALUTEPLATE_H
