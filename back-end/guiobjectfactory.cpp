#include "guiobjectfactory.h"
#include "box.h"
#include "utils.h"
#include "head.h"

GuiObjectFactory::GuiObjectFactory() {}

ItemWorld *GuiObjectFactory::generate(const QString &name) {
    ItemWorld *obj = nullptr;
    if (name == "Box") {
        obj = new Box(rand() % 100, 0);
    }

    return obj;
}
