#include "controller.h"
#include <cmath>
#include <ctime>

Controller::Controller() {
    srand(static_cast<unsigned int>(time(nullptr)));
    timer = new QTimer();
    timer->setInterval(33);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    startTimer();
}

void Controller::setDeviceSize(QPoint deviceSize) {
    Global::deviceSize = deviceSize;
}

void Controller::update() {
    world.render();
}

void Controller::startTimer() {
   timer->start();
}

void Controller::stopTimer() {
    timer->stop();
}

