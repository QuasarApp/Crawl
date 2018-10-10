#include "itemworld.h"
#include <cmath>
#include <QDateTime>
#include <QDebug>
#include <QRectF>

ItemWorld::ItemWorld(double x, double y) {
    this->x = x;
    this->y = y;
}

void ItemWorld::setSpeed(double *value) {
    speed = value;
}

void ItemWorld::setBeckGroundObject(bool value)
{
    beckGroundObject = value;
}

void ItemWorld::setSize(double x, double y) {
    sizeX = x;
    sizeY = y;
}

void ItemWorld::render() {
    qint64 tempTime = QDateTime::currentMSecsSinceEpoch() - time;
    double mx = x + *speed;
    x += (mx - x) / 1000 * tempTime;
    time = QDateTime::currentMSecsSinceEpoch();
}

bool ItemWorld::checkContact(const QRectF &riger) {

    bool result = riger.intersects(QRectF(x,y,sizeX, sizeY));

    return result && !beckGroundObject;
}

bool ItemWorld::isBeckGroundObject() {
    return beckGroundObject;
}

ItemWorld::~ItemWorld()
{

}
