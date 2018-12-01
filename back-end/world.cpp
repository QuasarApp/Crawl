#include "background.h"
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

QMultiMap<QString, ItemWorld *> World::getItems() const
{
    return items;
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

            items.insertMulti(name, obj);
        }

    } else {
        for ( int i = count; i < 0; ++i ) {
            auto obj = items.value(name);
            if (1 != items.remove(name, obj)) {
                qWarning() << "World::changeCountObjects error delete object!";
            }
            delete obj;
        }
    }
}

QMap<int, GuiObject *> World::init(WorldRules rules) {

    QMap<int, GuiObject*> res;

//    rules["BackGround"] = 1;

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

    auto snakeItems = snake.init(20, &spead);

    for (auto i = snakeItems.begin(); i != snakeItems.end(); ++i) {
        res.insert(i.key(), i.value());
    }

    for (auto i : items) {
        res[i->guiId()] = i;
    }


    oldRules = rules;
    time = QDateTime::currentMSecsSinceEpoch();
    defiat = false;
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

    for (auto i = items.begin(); i != items.end(); ++i) {
        defiat |= (*i)->move(rig, dx);
        (*i)->render();
    }

    defiat |= (rig->y()< 0 || rig->y() > 100);

    if (!snake.isDead() && defiat) {
        snake.kill();
    }

    currentLong += dx;
}

void World::resetPosition() {
    for (auto i : items) {
        i->reset();
    }
    spead = 0;

    snake.resetPosotion();
}

bool World::move() {
    return isEnd();
}

bool World::isEnd() {
    return currentLong >= endLong;
}

bool World::isDefiat() const {
    return defiat && !static_cast<bool>(spead);
}

WorldRules World::currentRules() const {
    return oldRules;
}

void World::reversClick() {
    if (snake.isDead()) {
        spead = 0;
        return;
    }

    snake.reverse();
    spead += d_spead;
}
