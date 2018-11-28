#include "background.h"

BackGround::BackGround(double x, double y): ItemWorld (x, y) {
    this->setSize(200, 4000);
    this->setTexture("qrc:/texture/box-texture");
    setBeckGroundObject(true);
}

void BackGround::render() {
    if (m_x + w() < 0) {
        m_x = w() * 0.5;
        emit xChanged(m_x);
    }
}

void BackGround::reset() {
   setX(-10 - (m_x + w()));
}
