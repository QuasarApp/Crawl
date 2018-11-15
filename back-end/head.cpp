#include "head.h"
#include <cmath>
#include <QDateTime>

void Head::render(){
    qint64 tempTime = QDateTime::currentMSecsSinceEpoch() - time;
    double my = m_rect.y() + *speed * sin(m_angle * TO_RADIAN);
    auto dy = (my - m_rect.y()) / 1000 * tempTime;
    m_rect.moveTop(m_rect.y() + dy);
    time = QDateTime::currentMSecsSinceEpoch();
    emit rectChanged(m_rect);
}

Head::Head(const QRectF &rect, double *spead):
    GuiObject () {
    setRect(rect);
    this->speed = spead;
}

Head::~Head() {
    
}
