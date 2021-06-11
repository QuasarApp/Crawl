#include "iground.h"
#include "iworld.h"

IGround::IGround()
{

}

void IGround::render(unsigned int ) {
    const IWorldItem *playerObject = getPlayer();
    QVector3D camera = world()->cameraReleativePosition();

    if (playerObject->position().x() - position().x() >
            camera.z() * 2) {
        setX(playerObject->position().x() + camera.z() * 4);
    }
}
