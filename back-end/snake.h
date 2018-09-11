#ifndef SNAKE_H
#define SNAKE_H

#define SPEEDSNAKE 10

#include <QVector>
#include "head.h"
class Snake
{
private:
    QVector<Head*> _items;
    double _speed;
    bool _isClick;
public:
    Snake();
    bool init(int size, double spead);
    const QVector<Head*>& getItems() const;
    void setSpeedHead (void);
};

#endif // SNAKE_H
