#include "SnakeProject/iworld.h"
#include "world.h"

inline void initResources() { Q_INIT_RESOURCE(Empty); }

extern "C" IWorld* instance() {
    initResources();
    return new World();
}
