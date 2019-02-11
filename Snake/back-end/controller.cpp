#include "controller.h"
#include <QThread>
#include <cmath>
#include <ctime>
#include "diff.h"
#include "lvls.h"
#include "reactor.h"

Controller::Controller() {
    srand(static_cast<unsigned int>(time(nullptr)));

    reactor = new Reactor([this]() {

        world.render();
        if(world.isDefiat()) {
            stopTimer();
            emit finished(false, lvl, world.getCurrentLong());
        }

        if (world.isEnd()) {
            stopTimer();
            emit finished(true, lvl, world.getCurrentLong());
        }

        emit long_changed(static_cast<int>(world.getCurrentLong()));
        emit generalLongchanged(generalLong());

    });
}

Controller::~Controller() {
    delete reactor;
}

bool Controller::nextLvl() {
    if (lvl + 1 >= lvls.size()) {
        return true;
    }
    m_generalLong += static_cast<int>(world.getCurrentLong());

    generateDiff(world.init(lvls.value(++lvl)));
    startTimer();


    return false;
}

void Controller::generateDiff(const QMap<int, GuiObject *>& objs) {

    auto removeIds = objectsContainer.keys();
    QList<int> addedIds;

    for (auto i = objs.begin(); i != objs.end(); ++i) {
        if (objectsContainer.contains(i.key())) {
            removeIds.removeOne(i.key());
        } else {
            objectsContainer.insert(i.key(), i.value());
            addedIds.push_back(i.key());
        }
    }

    if (removeIds.size() || addedIds.size()) {
        Diff diff;

        diff.setRemoveIds(removeIds);
        diff.setAddedIds(addedIds);
        emit gameObjectsChanged(diff);
    }
}

void Controller::newGame() {

    world.resetPosition();

    WorldRules newGameRules = lvls.first();
    lvl = 0;
    m_generalLong = 0;
    generateDiff(world.init(newGameRules));
    startTimer();
}

QObject *Controller::getGameObject(int id) {
    return objectsContainer.value(id, nullptr);
}

void Controller::startTimer() {
    reactor->start();
}

void Controller::stopTimer() {
    reactor->stop();
}

int Controller::long_() const {
    return static_cast<int>(world.getCurrentLong());
}

int Controller::generalLong() const {
    return m_generalLong + long_();
}

void Controller::buttonPress() {
    world.reversClick();
}

void Controller::setPause(bool p){
    reactor->setPause(p);
    if (!reactor->pause()) {
        world.unPause();
    }
}

