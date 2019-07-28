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
    setH(h);
    setW(w);
}

void ItemWorld::setLoc(double x, double y) {
    setX(x);
    setY(y);
}

void ItemWorld::render() {
    if (m_x + w() < 0) {
        m_x = (rand() % 400) + 200;
        m_y = rand() % 100;
        emit xChanged(m_x);
        emit yChanged(m_y);
    }
}

bool ItemWorld::move(const GuiObject *snakeRiger, double dx) {
    m_x -= dx;
    emit xChanged(m_x);

    return snakeRiger->rect().intersects(rect()) && !beckGroundObject;
}

bool ItemWorld::isBeckGroundObject() {
    return beckGroundObject;
}

ItemWorld::~ItemWorld() {}
