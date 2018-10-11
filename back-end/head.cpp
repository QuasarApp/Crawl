#include "head.h"
#include <cmath>
#include <QDateTime>

void Head::render(){
    qint64 tempTime = QDateTime::currentMSecsSinceEpoch() - time;
    double my = m_rect.y() + *speed * sin(m_angle * TO_RADIAN);
    auto dy = (my - m_rect.y()) / 1000 * tempTime;
    m_rect.setY(m_rect.y() + dy);
    time = QDateTime::currentMSecsSinceEpoch();
}

Head::Head(double *spead) {
    this->speed = spead;
}

Head::~Head() {
    
}
