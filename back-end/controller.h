#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QTime>
#include "snake.h"
#include "world.h"

class Controller : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QPoint deviceSize WRITE setDeviceSize)
private:
    World world;
    QTimer *timer;

public:
    Controller();
    void startTimer();
    void stopTimer();

public slots:
    void setDeviceSize(QPoint deviceSize);
    void update();
};

#endif // CONTROLLER_H
