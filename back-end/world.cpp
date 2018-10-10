#include "world.h"

#include <QMap>
#include "guiobject.h"
#include "guiobjectfactory.h"
#include <QDebug>
#include <QRectF>

World::World() {
    currentLong = 0;
    endLong = 0;
    background = "";
}

void World::clearItems() {
    for (auto i : items) {
        delete i;
    }
    items.clear();
}

QMap<int, GuiObject *> World::init(const WorldRules &rules) {

    QMap<int, GuiObject*> res;

    clearItems();

    currentLong = -1;
    for (auto i = rules.begin(); i != rules.end(); ++i) {
        if (i.key() == "Long") {
            endLong = rules["Long"];
            currentLong = 0;
        }
        else {

            auto size = i.value();
            for ( int j = 0; j < size; ++i ) {
                auto obj = GuiObjectFactory::generate(i.key());

                if (!obj) {
                    qWarning() <<"object not created line:" << Q_FUNC_INFO;
                    break;
                }

                obj->setSpeed(&spead);

                items.push_back(obj);
                res[obj->getId()] = obj;
            }
        }
    }

    return res;
}

World::~World() {
    clearItems();
}

void World::render() {

    snake.render();
    QRectF rig = snake.getRiger();

    for (int i = items.length(); i >= 0; --i) {
        items[i]->render();
        defiat |= items[i]->checkContact(rig);
    }
}

bool World::move(double spead) {
    this->spead = spead;
    currentLong += spead;
    return isEnd();
}

bool World::isEnd() {
    return currentLong >= endLong;
}

bool World::isDefiat() const {
    return defiat;
}

const QVector<ItemWorld *> &World::getItems() const {
    return items;
}
