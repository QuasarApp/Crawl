#include "engine.h"

#include <QQmlComponent>
#include <guiobject.h>

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

void Engine::setWorld(const IWorld *world) {

}
