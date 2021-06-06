#include "head.h"
#include <cmath>
#include <QDateTime>

void Head::render() {


    qint64 tempTime = QDateTime::currentMSecsSinceEpoch() - time;
    time = QDateTime::currentMSecsSinceEpoch();

    float u = ratation().toEulerAngles().z();
    double dy = (*speed) * sin(u * TO_RADIAN) / 1000 * tempTime;
    setY(position().y() + dy);

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
    setMash("qrc:/mesh/res/meshes/cube.mesh");
}

Head::~Head() {
    
}
