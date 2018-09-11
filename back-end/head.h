#ifndef HEAD_H
#define HEAD_H
#define TO_RADIAN 0.017453293


#include "baseclass.h"
#include <QString>

class Head : BaseClass
{
private:
    double _x, _y, _angle;
    QString _texture;
    qint64 _time;
    double *_speed;
public:
    Head(double *spead);
    double getAngle() const;
    void setAngle(double angle);

    double getY() const;
    void setY(double y);

    double getX() const;
    void setX(double x);

    double getSpeed() const;
    void setSpeed(double *value);
    
    void render();

    ~Head();
    
};

#endif // HEAD_H
