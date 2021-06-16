#include "engine.h"

#include <QQmlComponent>
#include <Crawl/guiobject.h>
#include "Crawl/iworld.h"
#include <quasarapp.h>
#include "Crawl/icontrol.h"

Engine::Engine(QObject *parent): QObject(parent) {

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
        _currentWorld->deinit();
    }

    _currentWorld = world;

    if (!_currentWorld->init()) {
        QuasarAppUtils::Params::log("Failed to init world. World name: " + _currentWorld->name(),
                                    QuasarAppUtils::Error);

        _currentWorld = nullptr;
        return;
    }

    if (!_currentWorld->userInterface()->init()) {
        return;
    }

    setMenu(_currentWorld->userInterface());

    emit worldChanged();

}

QString Engine::hdr() const {
    if (!_currentWorld)
        return "";

    return _currentWorld->hdrMap();
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

void Engine::setPrepareLvlProgress(int newPrepareLvlProgress) {
    if (_prepareLvlProgress == newPrepareLvlProgress) {
        return;
    }
    _prepareLvlProgress = newPrepareLvlProgress;
    emit prepareLvlProgressChanged();
}
