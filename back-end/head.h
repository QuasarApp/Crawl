#ifndef HEAD_H
#define HEAD_H

#include "baseclass.h"
#include <QString>

class Head : BaseClass
{
private:
    double x,y,angle;
    QString texture;
public:
    Head();
    double getAngle() const;
    void setAngle(double angle);

    double getY() const;
    void setY(double y);

    double getX() const;
    void setX(double x);

    ~Head();
};

#endif // HEAD_H
