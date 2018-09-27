#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "snake.h"
#include "world.h"

class Controller : public QObject
{
private:
    Snake snake;
    World world;

public:
    Controller();
    void update();
};

#endif // CONTROLLER_H
