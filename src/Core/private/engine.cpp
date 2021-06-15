#include "engine.h"

#include <QQmlComponent>
#include <SnakeProject/guiobject.h>
#include "SnakeProject/iworld.h"
#include <quasarapp.h>
#include "SnakeProject/icontrol.h"

Engine::Engine(QObject *parent): QObject(parent) {

}

QObject *Engine::scane() {
    return _scane;
}

void Engine::handleGameObjectsChanged(Diff diff) {

    int count = diff.addedIds.size() + diff.removeIds.size();
    int currentCount = 0;

    for (const auto &item: qAsConst(diff.addedIds)) {
        add(item);
        currentCount++;
        setPrepareLvlProgress((count / currentCount) * 100);
    }

    for (int id: qAsConst(diff.removeIds)) {
        remove(id);
        currentCount++;
        setPrepareLvlProgress((count / currentCount) * 100);
    }
}

bool Engine::add(GuiObject *obj) {

    if (!_engine)
        return false;

    if (!_scane)
        return false;

    // Using QQmlComponent
    QQmlComponent component(_engine,
            QUrl::fromLocalFile("MyItem.qml"),
                            _scane);
    QObject *object = component.create();

    if (!object)
        return false;

    if (!object->setProperty("model", QVariant::fromValue(obj)))
        return false;

    _qmlObjects.insert(obj->guiId(), object);

    return true;
}

bool Engine::remove(int id) {
    if (!_qmlObjects.contains(id)) {
        return false;
    }

    _qmlObjects[id]->deleteLater();
    _qmlObjects.remove(id);

    return true;
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
        disconnect(_currentWorld, &IWorld::sigOBjctsListChanged,
                   this, &Engine::handleGameObjectsChanged);

        _currentWorld->deinit();
    }

    _currentWorld = world;

    connect(_currentWorld, &IWorld::sigOBjctsListChanged,
            this, &Engine::handleGameObjectsChanged,
            Qt::QueuedConnection);

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

void Engine::setPrepareLvlProgress(int newPrepareLvlProgress) {
    if (_prepareLvlProgress == newPrepareLvlProgress) {
        return;
    }
    _prepareLvlProgress = newPrepareLvlProgress;
    emit prepareLvlProgressChanged();
}
