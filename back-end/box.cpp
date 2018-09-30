#include "box.h"

Box::Box(double *speed, double x, double y):
    ItemWorld (speed, x, y)
{
    this->setSize(10, 10);
    this->setTexture("qrc:/texture/box-texture");
}

