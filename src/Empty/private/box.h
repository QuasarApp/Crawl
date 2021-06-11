#ifndef BOX_H
#define BOX_H
#include "SnakeProject/iworlditem.h"

class Box: public IWorldItem {

public:
    Box();

    // IWorldItem interface
protected:
    void onIntersects(const IWorldItem *item) override;
};

#endif // BOX_H
