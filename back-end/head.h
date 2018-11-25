#ifndef HEAD_H
#define HEAD_H
#define TO_RADIAN 0.017453293


#include "guiobject.h"
#include <QString>

class Head : public GuiObject
{
private:
    qint64 time;
    double *speed;
public:
    Head(double x , double y, double h, double w, double *speed);
    void setAngle(double angle) override;
    void render() override;
    void reset() override;
    ~Head() override;
};

#endif // HEAD_H
