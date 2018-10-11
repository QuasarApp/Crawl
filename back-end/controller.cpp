#include "controller.h"
#include <cmath>
#include <ctime>

Controller::Controller() {
    srand(static_cast<unsigned int>(time(nullptr)));
}

void Controller::setDeviceSize(QPoint deviceSize) {
    Global::deviceSize = deviceSize;
}
