//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "engine.h"

#include <QQmlComponent>
#include <Crawl/guiobject.h>
#include "Crawl/iworld.h"
#include <QThread>
#include <quasarapp.h>
#include "Crawl/icontrol.h"
#include "QDateTime"
#include "QtConcurrent"

namespace CRAWL {

Engine::Engine(QObject *parent): QObject(parent) {

}

Engine::~Engine() {
    stopRenderLoop();
}

QObject *Engine::scane() {
    return _scane;
}

void Engine::setQmlEngine(QQmlEngine *newEngine) {
    if (_engine == newEngine)
        return;

    _engine = newEngine;
}

void Engine::setWorld(IWorld *world) {
    if (_currentWorld == world)
        return ;

    if (_currentWorld) {
        _currentWorld->reset();
    }

    _currentWorld = world;
    emit worldChanged();

    if (!prepareNewWorld()) {
        QuasarAppUtils::Params::log("Failed to init world. World name: " + _currentWorld->name(),
                                    QuasarAppUtils::Error);

        _currentWorld = nullptr;
        return;
    }

    startRenderLoop();
    _currentWorld->runAsBackGround();
}

void Engine::setScane(QObject *newScane) {
    if (_scane == newScane)
        return;
    _scane = newScane;
    emit scaneChanged();
}

QObject *Engine::player() const {
    if (_currentWorld)
        return _currentWorld->_player;

    return nullptr;
}

QObject *Engine::world() const {
    return _currentWorld;
}


QObject *Engine::menu() const {
    return _menu;
}

void Engine::setMenu(QObject *newMenu) {
    if (_menu == newMenu) {
        return;
    }

    _menu = newMenu;
    emit menuChanged();
}

int Engine::prepareLvlProgress() const {
    return _prepareLvlProgress;
}

bool Engine::start() const {
    if (!_currentWorld)
        return false;

    if (!_currentWorld->isInit())
        return false;

    return _currentWorld->start();
}

QObject *Engine::getGameObject(int id) const {
    if (!_currentWorld)
        return nullptr;

    return _currentWorld->getItem(id);
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

void Engine::setPrepareLvlProgress(int newPrepareLvlProgress) {
    if (_prepareLvlProgress == newPrepareLvlProgress) {
        return;
    }
    _prepareLvlProgress = newPrepareLvlProgress;
    emit prepareLvlProgressChanged();
}

bool Engine::prepareNewWorld() {
    if (!_currentWorld->prepare()) {
        return false;
    }

    if (!_currentWorld->userInterface()->init()) {
        return false;
    }

    setMenu(_currentWorld->userInterface());

    return true;
}

void Engine::renderLoop() {

    if (!_currentWorld)
        return;

    while (_renderLoop) {

        quint64 currentTime = QDateTime::currentMSecsSinceEpoch();

        if (!_oldTimeRender) {
            _oldTimeRender = currentTime;
            continue;
        }

        _currentWorld->render(currentTime - _oldTimeRender);
        _oldTimeRender = currentTime;
    }


}

}
