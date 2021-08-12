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
#include "store.h"

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

void Engine::setLevel(ILevel *world) {
    if (_currentLevel == world)
        return ;

    if (_currentLevel) {
        _currentLevel->reset();
    }

    _currentLevel = world;
    emit worldChanged();

    if (_currentLevel && _currentLevel->world() && !_currentLevel->world()->)) {

        if (_currentLevel->world()) {
            QuasarAppUtils::Params::log("Failed to init world. World name: " + _currentLevel->world()->itemName(),
                                        QuasarAppUtils::Error);
        } else {
            QuasarAppUtils::Params::log("Failed to init world. The World object is null! ",
                                        QuasarAppUtils::Error);
        }

        _currentLevel = nullptr;
        return;
    }

    startRenderLoop();
    _currentLevel->world()->runAsBackGround();
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
    return _currentLevel->world();
}

int Engine::prepareLvlProgress() const {
    return _prepareLvlProgress;
}

bool Engine::start() const {
    if (!_currentLevel)
        return false;

    if (!_currentLevel->isInit())
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
