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

void World::clear() {
    clearItems();
    snake.clear();
}

double World::getCurrentLong() const {
    return currentLong;
}

void World::clearItems() {
    for (auto i : items) {
        delete i;
    }
    oldRules.clear();
    items.clear();
    spead = 0;
    d_spead = 0;
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

    currentLong = -1;
    for (auto i = rules.begin(); i != rules.end(); ++i) {
        if (i.key() == "Long") {
            endLong = rules["Long"];
            currentLong = 0;
        }
        else if (i.key() == "Spead") {
            d_spead = rules["Spead"];
        }
        else {
            changeCountObjects(i.key(), i.value() - oldRules.value(i.key()));
        }
    }

    auto snakeItems = snake.init(10, &spead);

    for (auto i = snakeItems.begin(); i != snakeItems.end(); ++i) {
        res.insert(i.key(), i.value());
    }

    for (auto i : items) {
        res[i->guiId()] = i;
    }


    oldRules = rules;
    time = QDateTime::currentMSecsSinceEpoch();
    defiat = false;
    spead = 0;
    return res;
}

World::~World() {
    clearItems();
}

void World::render() {

    qint64 tempTime = QDateTime::currentMSecsSinceEpoch() - time;
    time = QDateTime::currentMSecsSinceEpoch();
    double dx = spead / 1000 * tempTime;

    spead -= 0.0310 * tempTime;

    if (spead < 0)
        spead = 0;

    snake.render();
    auto rig = snake.getItems().first();

    for (int i = items.length() - 1; i >= 0; --i) {
        defiat |= items[i]->move(rig, dx);
        items[i]->render();
    }


    currentLong += dx;
}

void World::resetPosition() {
    for (auto i : items) {
        i->reset();
    }
    snake.resetPosotion();
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
    spead += d_spead;
}

const QVector<ItemWorld *> &World::getItems() const {
    return items;
}
