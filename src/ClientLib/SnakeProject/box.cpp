#include "box.h"

#include <QColor>

Box::Box(double x, double y):
    ItemWorld (x, y) {

    this->setSize(10, 10);
    setMash("qrc:/mesh/res/meshes/cube.mesh");

    setColor(QColor(100, 100, 100).name());
}

