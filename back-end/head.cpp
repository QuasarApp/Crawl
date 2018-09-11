#include "head.h"
#include <cmath>
#include <QDateTime>

double Head::getAngle() const {
    return _angle;
}

void Head::setAngle(double angle) {
    _angle = angle;
}

double Head::getY() const {
    return _y;
}

void Head::setY(double y) {
    _y = y;
}

double Head::getX() const {
    return _x;
}

void Head::setX(double x) {
    _x = x;
}

void Head::render(){
    qint64 tempTime = QDateTime::currentMSecsSinceEpoch() - _time;
    double my = _y + *_speed * sin(_angle * TO_RADIAN);
    _y += (my - _y) / 1000 * tempTime;
    _time = QDateTime::currentMSecsSinceEpoch();
}

double Head::getSpeed() const {
    return *_speed;
}

Head::Head(double *spead) {
    _speed = spead;
}

Head::~Head() {

}
