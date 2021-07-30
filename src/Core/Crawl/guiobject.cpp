//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "guiobject.h"

#include <QVector3D>

namespace CRAWL {


GuiObject::GuiObject(const QString &name, const QString &viewTempalte, QObject *ptr):
    QObject (ptr) {
    _viewTemplate = viewTempalte;
    _className = name;
    generateId();
    setRotation(QQuaternion::fromEulerAngles({0,0,0}));
}

const QString& GuiObject::color() const {
    return _color;
}

void GuiObject::setColor(const QString& color) {
    if (_color == color)
        return;

    _color = color;
    emit colorChanged(_color);
}

void GuiObject::generateId() {
    static int id = 0;
    setGuiId(id++);
}

bool GuiObject::visible() const {
    return _visible;
}

void GuiObject::setVisible(bool newVisible) {
    if (_visible == newVisible)
        return;
    _visible = newVisible;
    emit visibleChanged();
}

const QString &GuiObject::className() const {
    return _className;
}

void GuiObject::reset() {
    setX(0);
    setY(0);
    setZ(0);
}

QString GuiObject::viewTemplate() const {
    return _viewTemplate;
}

int GuiObject::guiId() const {
    return _guiId;
}

void GuiObject::setGuiId(int guiId) {
    if (guiId == _guiId)
        return;

    _guiId = guiId;
    emit guiIdChanged(guiId);
}

void GuiObject::setX(float newX) {
    if (qFuzzyCompare(_position.x(), newX))
        return;
    _position.setX(newX);
    emit positionChanged();
}

void GuiObject::setY(float newY) {
    if (qFuzzyCompare(_position.y(), newY))
        return;
    _position.setY(newY);
    emit positionChanged();
}

void GuiObject::setZ(float newZ) {
    if (qFuzzyCompare(_position.z(), newZ))
        return;
    _position.setZ(newZ);
    emit positionChanged();
}

void GuiObject::setDx(float newDx) {
    if (qFuzzyCompare(size().x(), newDx))
        return;
    _size.setX(newDx);
    emit sizeChanged();
}

void GuiObject::setDy(float newDy) {
    if (qFuzzyCompare(size().y(), newDy))
        return;
    _size.setY(newDy);
    emit sizeChanged();
}

void GuiObject::setDz(float newDz) {
    if (qFuzzyCompare(size().z(), newDz))
        return;
    _size.setZ(newDz);
    emit sizeChanged();
}

const QString &GuiObject::baseColorMap() const {
    return _baseColorMap;
}

const QString &GuiObject::roughnessMap() const {
    return _roughnessMap;
}

const QString &GuiObject::normalMap() const {
    return _normalMap;
}

const QString &GuiObject::emissiveMap() const {
    return _emissiveMap;
}

QVector3D GuiObject::center() const {
    return _position + (_size / 2);
}

bool GuiObject::intersects(const QVector3D &point) const {
    auto radius = _size / 2;
    float thisMidRadius = (radius.z() + radius.y() + radius.x()) / 3;
    return center().distanceToPoint(point) < thisMidRadius ;
}

bool GuiObject::intersects(const GuiObject &object) const {
    auto radius = _size / 2;
    auto objRadius = object.size() / 2;
    float thisMidRadius = (radius.z() + radius.y() + radius.x()) / 3;
    float objMidRadius = (objRadius.z() + objRadius.y() + objRadius.x()) / 3;

    return center().distanceToPoint(object.center()) < (thisMidRadius + objMidRadius);
}

const QVector3D &GuiObject::position() const {
    return _position;
}

void GuiObject::setposition(const QVector3D &newposition) {
    if (_position == newposition)
        return;
    _position = newposition;
    emit positionChanged();
}

const QVector3D &GuiObject::size() const {
    return _size;
}

void GuiObject::setSize(const QVector3D &newSize) {
    if (_size == newSize)
        return;
    _size = newSize;
    emit sizeChanged();
}

const QQuaternion &GuiObject::rotation() const {
    return _rotation;
}

void GuiObject::setRotation(const QQuaternion &newRotation) {
    if (_rotation == newRotation)
        return;
    _rotation = newRotation;
    emit rotationChanged();
}

const QString &GuiObject::mash() const {
    return _mash;
}

void GuiObject::setMash(const QString &newMash) {
    if (_mash == newMash)
        return;
    _mash = newMash;
    emit mashChanged();
}

void GuiObject::setBaseColorMap(const QString &baseColorMap) {
    if (_baseColorMap == baseColorMap)
        return;
    _baseColorMap = baseColorMap;
    emit baseColorMapChanged();
}


void GuiObject::setRoughnessMap(const QString &roughnessMap) {
    if (_roughnessMap == roughnessMap)
        return;
    _roughnessMap = roughnessMap;
    emit roughnessMapChanged();
}


void GuiObject::setNormalMap(const QString &normalMap) {
    if (_normalMap == normalMap)
        return;
    _normalMap = normalMap;
    emit normalMapChanged();
}

void GuiObject::setEmissiveMap(const QString &emissiveMap) {
    if (_emissiveMap == emissiveMap)
        return;
    _emissiveMap = emissiveMap;
    emit emissiveMapChanged();
}

}
