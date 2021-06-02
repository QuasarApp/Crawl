#include "controller.h"
#include <cmath>
#include <ctime>
#include "diff.h"
#include "lvls.h"
#include "mainmenumodel.h"
#include "qmlnotifyservice.h"

Controller::Controller() {
    srand(static_cast<unsigned int>(time(nullptr)));
    timer = new QTimer();
    timer->setInterval(1);

    _networkModel = new MainMenuModel(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    connect(_networkModel, &MainMenuModel::newGame, this, &Controller::handleNewGame);

}

Controller::~Controller() {

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

void Controller::update() {
    if (pause) {
        return;
    }

    world.render();

    if(world.isDefiat()) {
        stopTimer();
        if (!_showMenu) {
            setShowMenu(true);
        }
        handleNewGame();
    }

    if (world.isEnd()) {
        stopTimer();

        if (!_showMenu) {


            if (auto service = QmlNotificationService::NotificationService::getService()) {
                QmlNotificationService::NotificationData notify(tr(" Next Lvl!!!"),
                                        tr(" You anblock next lvl (%0)" ).arg(lvl),
                                        "qrc:/texture/up");
                service->setNotify(notify);
            }
        }

        nextLvl();

    }

    emit long_changed(static_cast<int>(world.getCurrentLong()));
    emit generalLongchanged(generalLong());

}

void Controller::handleNewGame() {

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
    timer->start();
}

void Controller::stopTimer() {
    timer->stop();
}

int Controller::long_() const {
    return static_cast<int>(world.getCurrentLong());
}

int Controller::generalLong() const {
    return m_generalLong + long_();
}

QObject *Controller::mainMenuModel() const {
    return _networkModel;
}

void Controller::buttonPress() {
    world.reversClick();
}

void Controller::setPause(bool p){
    pause = p;
    if (!pause) {
        world.unPause();
    }
}

bool Controller::showMenu() const {
    return _showMenu;
}

void Controller::setShowMenu(bool showMenu) {
    if (_showMenu == showMenu)
        return;

    _showMenu = showMenu;
    emit showMenuChanged(_showMenu);
}

