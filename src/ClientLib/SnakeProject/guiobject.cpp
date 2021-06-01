#include "guiobject.h"

GuiObject::GuiObject(const QString &viewTempalte, QObject *ptr):
    QObject (ptr) {
    _viewTemplate = viewTempalte;
    generateId();

}

void GuiObject::render() {
}

QString GuiObject::color() const {
    return _color;
}

void GuiObject::setColor(QString color) {
    if (_color == color)
        return;

    _color = color;
    emit colorChanged(_color);
}

void GuiObject::generateId() {
    static int id = 0;
    _guiId = id++;
}

void GuiObject::reset() {
    setX(-1);
    setY(-1);
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

float GuiObject::x() const {
    return _x;
}

void GuiObject::setX(float newX) {
    if (qFuzzyCompare(_x, newX))
        return;
    _x = newX;
    emit xChanged();
}

float GuiObject::y() const {
    return _y;
}

void GuiObject::setY(float newY) {
    if (qFuzzyCompare(_y, newY))
        return;
    _y = newY;
    emit yChanged();
}

float GuiObject::z() const {
    return _z;
}

void GuiObject::setZ(float newZ) {
    if (qFuzzyCompare(_z, newZ))
        return;
    _z = newZ;
    emit zChanged();
}

float GuiObject::dx() const {
    return _dx;
}

void GuiObject::setDx(float newDx) {
    if (qFuzzyCompare(_dx, newDx))
        return;
    _dx = newDx;
    emit dxChanged();
}

float GuiObject::dy() const {
    return _dy;
}

void GuiObject::setDy(float newDy) {
    if (qFuzzyCompare(_dy, newDy))
        return;
    _dy = newDy;
    emit dyChanged();
}

float GuiObject::dz() const {
    return _dz;
}

void GuiObject::setDz(float newDz) {
    if (qFuzzyCompare(_dz, newDz))
        return;
    _dz = newDz;
    emit dzChanged();
}

float GuiObject::rx() const {
    return _rx;
}

void GuiObject::setRx(float newRx) {
    if (qFuzzyCompare(_rx, newRx))
        return;
    _rx = newRx;
    emit rxChanged();
}

float GuiObject::ry() const {
    return _ry;
}

void GuiObject::setRy(float newRy) {
    if (qFuzzyCompare(_ry, newRy))
        return;
    _ry = newRy;
    emit ryChanged();
}

float GuiObject::rz() const {
    return _rz;
}

void GuiObject::setRz(float newRz) {
    if (qFuzzyCompare(_rz, newRz))
        return;
    _rz = newRz;
    emit rzChanged();
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
