#ifndef ITEMWORLD_H
#define ITEMWORLD_H


#include "baseclass.h"
#include <QString>

class ItemWorld : BaseClass
{
private:
    double x, y;
    QString *texture;
    double sizeX, sizeY, radius;
    qint64 time;
    double *speed;
public:
    ItemWorld(double *speed);

    double getX() const;
    void setX(double value);

    double getY() const;
    void setY(double value);

    virtual void setSize(double x, double y);

    void render();

    QString *getTexture() const;
    void setTexture(QString *value);

    ~ItemWorld();
};

#endif // ITEMWORLD_H
