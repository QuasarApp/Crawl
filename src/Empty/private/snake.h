#ifndef SNAKE_H
#define SNAKE_H

#include "SnakeProject/iplayer.h"

class Snake : public IPlayer {


    // IWorldItem interface
protected:
    void onIntersects(const IWorldItem *item) override;
};

#endif // SNAKE_H
