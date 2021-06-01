#include "itemworld.h"
#include "snakeutils.h"
#include <cmath>
#include <QDebug>
#include <QRectF>

#define POINT 100

ItemWorld::ItemWorld(double x, double y, const QString& guiTemplate):
    GuiObject3D (guiTemplate) {
    setLoc(x, y);
}

void ItemWorld::setBeckGroundObject(bool value) {
    beckGroundObject = value;
}

void ItemWorld::setSize(double h, double w) {
    setH(h);
    setW(w);
}

void ItemWorld::setLoc(double x, double y) {
    setX(x);
    setY(y);
}

void ItemWorld::render() {
    if (_x + w() < 0) {
        _x = (rand() % 400) + 200;
        _y = rand() % 100;
        emit xChanged();
        emit yChanged();
    }
}

bool ItemWorld::move(const GuiObject *snakeRiger, double dx) {
    _x -= dx;
    emit xChanged();

    return snakeRiger->rect().intersects(rect()) && !beckGroundObject;
}

bool ItemWorld::isBeckGroundObject() {
    return beckGroundObject;
}

ItemWorld::~ItemWorld() {}
