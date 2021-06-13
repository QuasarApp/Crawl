#include "box.h"
#include "plate.h"
#include "world.h"
#include <snake.h>
#include "SnakeProject/iworlditem.h"

IGround *World::generateGroundTile() {
    return new Plate();
}

IPlayer *World::initPlayer() const {
    return new Snake();
}

WorldRule *World::initWorldRules() const {
    return new WorldRule {
        {0, {{"Box", 10}}}
    };
}

QString World::initHdrBackGround() const {
    return "qrc:/hdr/res/hdr/testHDR.jpg";
}

QString World::description() const {
    return "This a test lvl";
}

QString World::imagePreview() const {
    return "qrc:/hdr/res/hdr/testHDR.jpg";

}

QString World::name() const {
    return "Test";
}

int World::costToUnlock() const {
    return 0;
}

QVector3D World::initCameraPosition() {
    return {0, 0, 100};
}

IWorldItem *World::generate(const QString &objectType) const {
    if (objectType == "Box") {
        return new Box();
    }

    return nullptr;
}
