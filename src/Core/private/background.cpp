#include "background.h"

BackGround::BackGround(double x, double y): ItemWorld (x, y) {
    this->setSize(200, 400);
    setBeckGroundObject(true);
}

void BackGround::render() {
    auto wPart = size().x() / 2;

    if (position().x() + wPart < 200) {
        setX(wPart);
    }
}

void BackGround::reset() {
   setX(0 - size().x());
   render();
}
