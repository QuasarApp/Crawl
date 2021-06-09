#include "plate.h"

Plate::Plate()
{
    setMash(":/mesh/res/meshes/cube.mesh");
    setSize({100,100,0});
    setZ(0);
}

void Plate::onIntersects(const IWorldItem *item) {
    Q_UNUSED(item)
}
