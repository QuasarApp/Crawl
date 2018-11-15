#include "itemworld.h"
#include "utils.h"
#include <cmath>
#include <QDebug>
#include <QRectF>

#define POINT 100

ItemWorld::ItemWorld(double x, double y) {
    setSize(x, y);
}

void ItemWorld::setBeckGroundObject(bool value) {
    beckGroundObject = value;
}

void ItemWorld::setSize(double x, double y) {
    QRectF rect;
    rect.setX(x);
    rect.setY(y);
    setRect(rect);
}

void ItemWorld::render() {
    if (m_rect.x() < 0) {
        m_rect.setX(rand() % 200);
        m_rect.setY(rand() % 100);
        emit rectChanged(m_rect);

    }
}

bool ItemWorld::move(const QRectF &snakeRiger, double dx) {
    m_rect.setX( m_rect.x() - dx);
    emit rectChanged(m_rect);

    return snakeRiger.intersects(m_rect) && !beckGroundObject;
}

bool ItemWorld::isBeckGroundObject() {
    return beckGroundObject;
}

ItemWorld::~ItemWorld() {}
