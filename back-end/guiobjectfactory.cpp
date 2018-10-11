#include "guiobjectfactory.h"
#include "box.h"
#include "utils.h"

GuiObjectFactory::GuiObjectFactory() {}

ItemWorld *GuiObjectFactory::generate(const QString &name) {
    ItemWorld *obj = nullptr;
    if (name == "Box") {
        obj = new Box(-Global::deviceSize.x(), 0);
    }

    return obj;
}
