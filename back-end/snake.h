#ifndef SNAKE_H
#define SNAKE_H

#define SPEEDSNAKE 10

#include <QVector>
#include "head.h"
#include "baseclass.h"

class GuiObject;

class Snake : public BaseClass
{
private:
    QVector<Head*> items;
    double speed = 0;
    bool isClick = false;
    int countClick = 0;
    void changeCountObjects(int count);

public:
    Snake();
    ~Snake() override;

    void reverse();
    const QRectF &getRiger() const;
    void render() override;
    QMap<int, GuiObject *> init(int size, double speed);
    bool isInited() const;
    const QVector<Head*>& getItems() const;
    double getMovedLong() const;
};

#endif // SNAKE_H
