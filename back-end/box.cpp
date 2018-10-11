#include "box.h"

Box::Box(double x, double y):
    ItemWorld (x, y) {

    this->setSize(10, 10);
    this->setTexture("qrc:/texture/box-texture");
}

