#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "snake.h"
#include "world.h"

class Controller : public QObject
{
    Q_OBJECT

private:
    World world;

public:
    Controller();
    void update();
};

#endif // CONTROLLER_H
