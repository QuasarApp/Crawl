#ifndef HEAD_H
#define HEAD_H
#define TO_RADIAN 0.017453293


#include "gui.h"
#include <QString>

class Head : public Gui
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
