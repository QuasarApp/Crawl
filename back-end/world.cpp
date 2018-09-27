#include "world.h"

World::World() :
    speed(SPEEDWORLD) {

}

World::~World() {
    for (auto i : items) {
        delete i;
    }
    items.clear();
}

void World::render()
{
    for (int i = items.length(); i >= 0; --i) {
        items[i]->render();
    }
}

const QVector<ItemWorld *> &World::getItems() const {
    return items;
}
