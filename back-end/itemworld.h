#ifndef ITEMWORLD_H
#define ITEMWORLD_H


#include "gui.h"
#include <QString>

class ItemWorld : public Gui
{
private:    
    qint64 time;
    double *speed;
public:
    ItemWorld(double *speed, double x, double y);

    virtual void setSize(double x, double y);

    void render();

    ~ItemWorld();
};

#endif // ITEMWORLD_H
