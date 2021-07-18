#ifndef WOOD_H
#define WOOD_H


#include <Crawl/iworlditem.h>
#include <jungle_global.h>

namespace JungleLvl {

class CRAWL_JUNGLE_LEVEL_EXPORT Wood: public CRAWL::IWorldItem
{
    Q_OBJECT
public:
    Wood();
    void onIntersects(const IWorldItem *);

};

}
#endif // WOOD_H
