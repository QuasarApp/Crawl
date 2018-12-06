#include "guiobjectfactory.h"
#include "box.h"
#include "utils.h"
#include "head.h"
#include "background.h"
#include "backgrounditem.h"

GuiObjectFactory::GuiObjectFactory() {}

ItemWorld *GuiObjectFactory::generate(const QString &name) {
    ItemWorld *obj = nullptr;
    if (name == "Box") {
        obj = new Box(rand() % 400, 0);
    }
    else if (name == "BackGround") {
        obj = new BackGround(0, 0);
    }
    else if (name == "BackGroundItem") {
        obj = new BackGroundItem(0, 0);
    }

    return obj;
}
