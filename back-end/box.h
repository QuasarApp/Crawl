#ifndef BOX_H
#define BOX_H

#include "itemworld.h"

class Box
{
private:
    double sizeX, sizeY, radius;
    QString texture;
public:
    Box();
    void setSize(double sizeX, double sizeY, double radius);

};

#endif // BOX_H
