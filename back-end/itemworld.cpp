#include "itemworld.h"
#include <cmath>
#include <QDateTime>

ItemWorld::ItemWorld(double *speed, double x, double y){
    this->speed = speed;
    this->x = x;
    this->y = y;
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

ItemWorld::~ItemWorld()
{

}
