#ifndef HEAD_H
#define HEAD_H
#define TO_RADIAN 0.017453293


#include "baseclass.h"
#include <QString>

class Head : BaseClass
{
private:
    double x, y, angle, speed;
    QString texture;
    qint64 time;
public:
    Head();
    double getAngle() const;
    void setAngle(double angle);

    double getY() const;
    void setY(double y);

    double getX() const;
    void setX(double x);

    double getSpeed() const;
    void setSpeed(double value);

    void render();

    ~Head();
};

#endif // HEAD_H
