#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "snake.h"
#include "world.h"

class Controller : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QPoint deviceSize WRITE setDeviceSize)
private:
    World world;

public:
    Controller();
    void update();
public slots:
    void setDeviceSize(QPoint deviceSize);
};

#endif // CONTROLLER_H
