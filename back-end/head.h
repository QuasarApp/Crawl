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
    Head(double *speed);
    
    void render();

    ~Head();
};

#endif // HEAD_H
