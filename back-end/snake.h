#ifndef SNAKE_H
#define SNAKE_H

#define SPEEDSNAKE 10

#include <QVector>
#include "head.h"
class Snake
{
private:
    QVector<Head*> items;
    double speed;
    bool isClick;
public:
    Snake();
    bool init(int size, bool click);
    void setItems(const QVector<Head *> &value);
    QVector<Head *> getItems() const;
    void setSpeedHead (void);
};

#endif // SNAKE_H
