//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

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
#include "store.h"

namespace CRAWL {

Engine::Engine(QObject *parent): QObject(parent) {
    _store = new Store();
    _currentUser = new User();
    _menu = new MainMenuModel();

}

Engine::~Engine() {
    stopRenderLoop();
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

    if (_currentLevel->world()) {
        QuasarAppUtils::Params::log("Failed to init world. World name: " +
                                    _currentLevel->world()->itemName(),
                                    QuasarAppUtils::Error);

        _currentLevel = nullptr;
        return;
    }

    startRenderLoop();
    _currentLevel->world()->runAsBackGround();

    connect(_currentLevel->previewScane(), &IPreviewScaneWorld::sigPrepareIsFinished,
            this, &Engine::start);

    connect(_currentLevel->world(), &IPreviewScaneWorld::sigGameFinished,
            this, &Engine::stop);
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


    if (!_currentLevel->world()->stop()) {
        return;
    }

    _currentLevel->previewScane()->start(_currentLevel->previewScane()->configuration());
}

QObject *Engine::getGameObject(int id) const {
    if (!_currentLevel)
        return nullptr;

    return _currentLevel->world()->getItem(id);
}

void Engine::startRenderLoop() {
    if (isRendering())
        return;

    _renderLoop = true;
    _renderLoopFuture = QtConcurrent::run([this](){renderLoop();});
}

void Engine::stopRenderLoop() {
    _renderLoop = false;
    _renderLoopFuture.waitForFinished();
}

bool Engine::isRendering() const {
    return _renderLoopFuture.isRunning();
}

void Engine::renderLoop() {

    if (!_currentLevel)
        return;

    while (_renderLoop) {

        quint64 currentTime = QDateTime::currentMSecsSinceEpoch();

        if (!_oldTimeRender) {
            _oldTimeRender = currentTime;
            continue;
        }

        _currentLevel->world()->render(currentTime - _oldTimeRender);
        _oldTimeRender = currentTime;
    }
}

QObject *Engine::menu() const {
    return _menu;
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


void Engine::initStore(const QMultiHash<int, const IItem *> &availabelItems) {
    _store->init(availabelItems);
    static_cast<StoreViewModel*>(_menu->storeView())->init(_store, _currentUser);
}

}
