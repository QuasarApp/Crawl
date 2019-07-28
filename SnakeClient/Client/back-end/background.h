#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "itemworld.h"


class BackGround : public ItemWorld
{
public:
    BackGround(double x, double y);

    void render() override;
    void reset() override;
};

#endif // BACKGROUND_H
