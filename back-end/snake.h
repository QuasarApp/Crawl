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
    double rataticonDistance = 1;
    QVector<Head*> items;
    double *speed = nullptr;
    bool isClick = false;
    int countClick = 0;
    void changeCountObjects(int count);

    double checDistance(int i);
    void clearItems();


public:
    Snake();
    ~Snake() override;
    void clear();
    void resetPosotion();

    void reverse();
    void render() override;
    QMap<int, GuiObject *> init(int size, double *speed);
    bool isInited() const;
    const QVector<Head*>& getItems() const;
    double getMovedLong() const;
    double getRataticonDistance() const;
    void setRataticonDistance(double value);
};

#endif // SNAKE_H
