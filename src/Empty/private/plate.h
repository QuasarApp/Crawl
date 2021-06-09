#ifndef PLATE_H
#define PLATE_H
#include "SnakeProject/iground.h"

class Plate: public IGround {
public:
    Plate();

    // IWorldItem interface
protected:
    void onIntersects(const IWorldItem *item) override;
};

#endif // PLATE_H
