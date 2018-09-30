#include "head.h"
#include <cmath>
#include <QDateTime>

void Head::render(){
    qint64 tempTime = QDateTime::currentMSecsSinceEpoch() - time;
    double my = y + *speed * sin(angle * TO_RADIAN);
    y += (my - y) / 1000 * tempTime;
    time = QDateTime::currentMSecsSinceEpoch();
}

Head::Head(double *spead) {
    this->speed = spead;
}

Head::~Head() {
    
}
