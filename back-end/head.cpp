#include "head.h"

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

Head::Head() {

}

Head::~Head() {

}
