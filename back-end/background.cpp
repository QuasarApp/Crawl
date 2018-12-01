#include "background.h"

BackGround::BackGround(double x, double y): ItemWorld (x, y) {
    this->setSize(200, 400);
    this->setTexture("qrc:/texture/asphalt");
    setBeckGroundObject(true);
}

void BackGround::render() {
    auto wPart = w() / 2;

    if (m_x + wPart < 200) {
        setX(wPart);
    }
}

void BackGround::reset() {
   setX(0 - w());
   render();
}
