#ifndef BACKGROUNDITEM_H
#define BACKGROUNDITEM_H

#include "itemworld.h"


class BackGroundItem : public ItemWorld
{
public:
    BackGroundItem(double x, double y);
    void reset() override;

};

#endif // BACKGROUNDITEM_H
