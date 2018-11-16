#include "world.h"

#include <QMap>
#include "guiobject.h"
#include "guiobjectfactory.h"
#include <QDateTime>
#include <QDebug>

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

void World::changeCountObjects(const QString &name, int count) {

    if (count > 0) {

        for ( int i = 0; i < count; ++i ) {
            auto obj = GuiObjectFactory::generate(name);

            if (!obj) {
                qWarning() <<"object not created line:" << Q_FUNC_INFO;
                break;
            }

            items.push_back(obj);
        }

    } else {
        for ( int i = count; i < 0; ++i ) {
            auto obj = items.first();
            items.removeFirst();
            delete obj;
        }
    }
}

QMap<int, GuiObject *> World::init(const WorldRules &rules) {

    QMap<int, GuiObject*> res;

    auto snakeItems = snake.init(10, 15);

    for (auto i = snakeItems.begin(); i != snakeItems.end(); ++i) {
        res.insert(i.key(), i.value());
    }

    currentLong = -1;
    for (auto i = rules.begin(); i != rules.end(); ++i) {
        if (i.key() == "Long") {
            endLong = rules["Long"];
            currentLong = 0;
        }
        else if (i.key() == "Spead") {
            spead = rules["Spead"];
        }
        else {
            changeCountObjects(i.key(), i.value() - oldRules.value(i.key()));
        }
    }

    for (auto i : items) {
        res[i->guiId()] = i;
    }


    oldRules = rules;
    return res;
}

World::~World() {
    clearItems();
}

void World::render() {

    qint64 tempTime = QDateTime::currentMSecsSinceEpoch() - time;
    time = QDateTime::currentMSecsSinceEpoch();
    auto dx = speed / 1000 * tempTime;

    snake.render();
    const QRectF &rig = snake.getRiger();

    for (int i = items.length() - 1; i >= 0; --i) {
        defiat |= items[i]->move(rig, dx);
        items[i]->render();
    }

    currentLong += dx;
}

bool World::move() {
    return isEnd();
}

bool World::isEnd() {
    return currentLong >= endLong;
}

bool World::isDefiat() const {
    return defiat;
}

WorldRules World::currentRules() const {
    return oldRules;
}

void World::reversClick() {
    snake.reverse();
}

const QVector<ItemWorld *> &World::getItems() const {
    return items;
}
