#include "head.h"
#include <cmath>
#include <QDateTime>

double Head::getAngle() const {
    return angle;
}

void Head::setAngle(double angle) {
    this->angle = angle;
}

double Head::getY() const {
    return y;
}

void Head::setY(double y) {
    this->y = y;
}

double Head::getX() const {
    return x;
}

void Head::setX(double x) {
    this->x = x;
}

void Head::render(){
    qint64 tempTime = QDateTime::currentMSecsSinceEpoch() - time;
    double my = y + *speed * sin(angle * TO_RADIAN);
    y += (my - y) / 1000 * tempTime;
    time = QDateTime::currentMSecsSinceEpoch();
}

double *Head::getSpeed() const
{
    return speed;
}

void Head::setSpeed(double *speed)
{
    this->speed = speed;
}

Head::Head() {

}

Head::~Head() {

}
