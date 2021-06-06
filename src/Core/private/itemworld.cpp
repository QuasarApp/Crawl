#include "itemworld.h"
#include "snakeutils.h"
#include <cmath>
#include <QDebug>
#include <QRectF>

#define POINT 100

ItemWorld::ItemWorld(double x, double y, const QString& guiTemplate):
    GuiObject (guiTemplate) {
    setLoc(x, y);
}

void ItemWorld::setBeckGroundObject(bool value) {
    beckGroundObject = value;
}

void ItemWorld::setSize(double h, double w) {
    setDx(h);
    setDy(w);
}

void ItemWorld::setLoc(double x, double y) {
    setX(x);
    setY(y);
}

void ItemWorld::render() {
    if (position().y() + size().y() < 0) {
        setX((rand() % 400) + 200);
        setY(rand() % 100);
    }
}

bool ItemWorld::move(const GuiObject *snakeRiger, double dx) {
    setX(position().x() - dx);

    return false;// snakeRiger->rect().intersects(rect()) && !beckGroundObject;
}

bool ItemWorld::isBeckGroundObject() {
    return beckGroundObject;
}

ItemWorld::~ItemWorld() {}
