#include "guiobjectfactory.h"
#include "box.h"
#include <cmath>
#include <ctime>

GuiObjectFactory::GuiObjectFactory() {

    srand(static_cast<unsigned int>(time(nullptr)));
}

ItemWorld *GuiObjectFactory::generate(const QString &name) {
    ItemWorld *obj = nullptr;
    if (name == "Box") {
        obj = new Box(100, rand() % 100); // x and y on %
    }

    return obj;
}
