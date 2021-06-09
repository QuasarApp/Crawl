#include "SnakeProject/iworld.h"
#include "world.h"

IWorld* instance() {
    return new World();
}
