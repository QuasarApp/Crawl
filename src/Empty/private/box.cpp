#include "box.h"


Box::Box() {
    setMash(":/mesh/res/meshes/cube.mesh");
    setSize({10,10,10});
    setZ(1);
}

void Box::onIntersects(const IWorldItem *item) {
    Q_UNUSED(item);
}
