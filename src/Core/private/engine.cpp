#include "engine.h"

#include <QQmlComponent>
#include <guiobject.h>
#include "SnakeProject/iworld.h"
#include "diff.h"

Engine::Engine() {

}

QObject *Engine::scane() {
    return _scane;
}

void Engine::handleGameObjectsChanged(Diff diff) {

    for (const auto &item: diff.getAddedIds()) {
        add(item);
    }

    for (int id: diff.getRemoveIds()) {
        remove(id);
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
    }

    _currentWorld = world;

    connect(_currentWorld, &IWorld::sigOBjctsListChanged,
            this, &Engine::handleGameObjectsChanged,
            Qt::QueuedConnection);

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
