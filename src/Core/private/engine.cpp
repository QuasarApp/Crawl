//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "availablelevelsmodel.h"
#include "engine.h"
#include "mainmenumodel.h"

#include <QQmlComponent>
#include <Crawl/guiobject.h>
#include <Crawl/ipreviewscaneworld.h>
#include "Crawl/iworld.h"
#include <QThread>
#include <quasarapp.h>
#include <storeviewmodel.h>
#include "Crawl/icontrol.h"
#include "QDateTime"
#include "QtConcurrent"
#include "offlinestore.h"

namespace CRAWL {

Engine::Engine(QObject *parent): QObject(parent) {
    _store = new OfflineStore();
    _menu = new MainMenuModel();

    setNewUser(new User());

}

Engine::~Engine() {


    for (auto it = _availableLvls.begin(); it != _availableLvls.end(); ++it) {
        delete it.value();
    }

    _availableLvls.clear();

    delete _menu;
    delete _currentUser;
}

QObject *Engine::scane() {
    return _scane;
}

void Engine::setLevel(ILevel *world) {

    if (_currentLevel == world)
        return ;

    if (_currentLevel) {
        _currentLevel->reset();
    }

    _currentLevel = world;
    emit worldChanged();

    if (!_currentLevel) {

        QuasarAppUtils::Params::log("Failed to init world. The World object is null! ",
                                    QuasarAppUtils::Error);

        _currentLevel = nullptr;
        return;
    }

    if (!_currentLevel->world()) {
        QuasarAppUtils::Params::log("Failed to init world. The World Object is null: " +
                                    _currentLevel->world()->itemName(),
                                    QuasarAppUtils::Error);

        _currentLevel = nullptr;
        return;
    }

    if (!_currentLevel->previewScane()) {
        QuasarAppUtils::Params::log("Failed to init world. The World Preview scane is null. World Name: " +
                                    _currentLevel->world()->itemName(),
                                    QuasarAppUtils::Error);

        _currentLevel = nullptr;
        return;
    }

    connect(_currentLevel->previewScane(), &IPreviewScaneWorld::sigPrepareIsFinished,
            this, &Engine::start);

    connect(_currentLevel->world(), &IPreviewScaneWorld::sigGameFinished,
            this, &Engine::stop);

    _currentLevel->previewScane()->start({});

}

void Engine::setScane(QObject *newScane) {
    if (_scane == newScane)
        return;
    _scane = newScane;
    emit scaneChanged();
}

QObject *Engine::player() const {
    if (_currentLevel && _currentLevel->world())
        return _currentLevel->world()->player();

    return nullptr;
}

QObject *Engine::world() const {
    if (!_currentLevel)
        return nullptr;

    return _currentLevel->world();
}

void Engine::start(const StartData& config) const {
    if (!_currentLevel)
        return;


    if (!_currentLevel->previewScane()->stop()) {
        return;
    }

    _currentLevel->world()->start(config);
}

void Engine::stop() const {
    if (!_currentLevel)
        return;

    _currentLevel->previewScane()->start(_currentLevel->previewScane()->configuration());
}

void Engine::handleUnlockedItem(int item) {
    auto itemObj = store()->getItemById(item);

    if (!itemObj)
        return;

    if (itemObj->itemType() == IWorld::type()) {
        static_cast<AvailableLevelsModel*>(_menu->selectLevelModle())->addKey(item);
    }
}

void Engine::handleDroppedItem(int item) {
    static_cast<AvailableLevelsModel*>(_menu->selectLevelModle())->removeKey(item);
}

void Engine::handleUnlockedItemsListChanged(const QSet<int> &newSet) {
    static_cast<AvailableLevelsModel*>(_menu->selectLevelModle())->setKeys(QList<int>(newSet.begin(), newSet.end()));
}

void Engine::handleLevelChanged(int levelId) {

    ILevel* data = _availableLvls.value(levelId, nullptr);

    if (!data) {
        QuasarAppUtils::Params::log("Failed to start lvl.", QuasarAppUtils::Error);
        return;
    }

    setLevel(data);
}

ILevel *Engine::getLastLevel() {
    for (const auto &data : qAsConst(_availableLvls)) {
        if (data && data->world() && currentUser() &&
               currentUser()->isUnlocked(data->world()->itemId())) {
            return data;
        }
    }

    return nullptr;
}

QObject *Engine::menu() const {
    return _menu;
}

void Engine::setNewUser(User *user) {
    if (_currentUser) {

        disconnect(_currentUser, &User::sigUnlcoked, this, &Engine::handleUnlockedItem);
        disconnect(_currentUser, &User::sigDropped, this, &Engine::handleDroppedItem);
        disconnect(_currentUser, &User::sigUlockedItemsChanged,
                   this, &Engine::handleUnlockedItemsListChanged);
    }

    _currentUser = user;
    static_cast<StoreViewModel*>(_menu->storeView())->setUser(_currentUser);
    static_cast<AvailableLevelsModel*>(_menu->selectLevelModle())->setUser(_currentUser);


    if (_currentUser) {

        connect(_currentUser, &User::sigUnlcoked, this, &Engine::handleUnlockedItem);
        connect(_currentUser, &User::sigDropped, this, &Engine::handleDroppedItem);
        connect(_currentUser, &User::sigUlockedItemsChanged,
                this, &Engine::handleUnlockedItemsListChanged);
    }
}

void Engine::addLvl(ILevel *levelWordl) {
    if (!levelWordl->world()) {
        QuasarAppUtils::Params::log("The Level not contains world object!!!");
        return;
    }
    _availableLvls.insert(levelWordl->world()->itemId(), levelWordl);
}

Store *Engine::store() const {
    return _store;
}

QObject *Engine::nest() const {
    if (!_currentLevel)
        return nullptr;

    return _currentLevel->previewScane();
}

User *Engine::currentUser() const {
    return _currentUser;
}

void Engine::init() {
    QList<int> availableWorlds;

    for (const auto &data : qAsConst(_availableLvls)) {
        if (data && data->world()) {
            if (data->world()->itemType() == IWorld::type() && _currentUser->isUnlocked(data->world()->itemId())) {
                availableWorlds.push_back(data->world()->itemId());
            }

            _store->addLevel(data);
        }
    }

    static_cast<StoreViewModel*>(_menu->storeView())->init(_store, _currentUser);

#define selectedLevelModel static_cast<AvailableLevelsModel*>(_menu->selectLevelModle())

    selectedLevelModel->setStore(_store);
    selectedLevelModel->setKeys(availableWorlds);

    connect(selectedLevelModel, &AvailableLevelsModel::sigUserSelectLevel,
            this, &Engine::handleLevelChanged);
}

}
