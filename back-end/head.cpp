#include "head.h"
#include <cmath>
#include <QDateTime>

void Head::render() {


    qint64 tempTime = QDateTime::currentMSecsSinceEpoch() - time;
    time = QDateTime::currentMSecsSinceEpoch();

    double my = (m_y + (*speed * 0.55) * sin(m_angle * TO_RADIAN));
    m_y += (my - m_y) / 1000 * tempTime;

    emit yChanged(m_y);
}

void Head::reset() {
}

Head::Head(double x, double y, double h, double w, double *spead):
    GuiObject () {
    setX(x);
    setY(y);
    setW(w);
    setH(h);
    this->speed = spead;
}

void Head::setAngle(double angle) {
    m_angle = angle;
    emit angleChanged(m_angle);
}

Head::~Head() {
    
}
