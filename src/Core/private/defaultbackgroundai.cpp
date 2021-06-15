#include "defaultbackgroundai.h"
#include <QTimer>

DefaultBackgroundAI::DefaultBackgroundAI() {
    _timer = new QTimer();
    _timer->setInterval(1000);
}

DefaultBackgroundAI::~DefaultBackgroundAI() {
    _timer->stop();
    delete _timer;
}

void DefaultBackgroundAI::startAI() {
    _timer->start();
}

void DefaultBackgroundAI::stopAI() {
    _timer->stop();
}

void DefaultBackgroundAI::handleTimerTriger() {
    _timer->setInterval(rand() % 1000  + 10);

    emit userTap();
}
