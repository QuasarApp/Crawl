#include "head.h"
#include <cmath>
#include <QDateTime>

void Head::render() {


    qint64 tempTime = QDateTime::currentMSecsSinceEpoch() - time;
    time = QDateTime::currentMSecsSinceEpoch();

    double my = (position().y() + (*speed * 0.55) * sin(ratation().scalar() * TO_RADIAN));
    setY((my - position().y()) / 1000 * tempTime);

    if (*speed < 1) {
        setColor(generalSpeadColor);

    } else if (*speed < normSpead) {
        setColor(normSpeadColor);

    } else if (*speed < fastSpead) {
        setColor(fastSpeadColor);

    } else if (*speed < megaFastSpead) {
        setColor(megaFastSpeadColor);

    }
}

void Head::reset() {
}

void Head::unPause() {
    time = QDateTime::currentMSecsSinceEpoch();
}

Head::Head(float x, float y, float h, float w, float thickness, float *spead):
    GuiObject ("SnakeItem") {
    setposition({x, y, 0});
    setSize({w, h, thickness});

    this->speed = spead;
    setMash("#Cube");
}

Head::~Head() {
    
}
