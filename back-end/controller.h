#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "snake.h"

class Controller : public QObject
{
private:
    Snake snake;
public:
    Controller();
    void update();
};

#endif // CONTROLLER_H
