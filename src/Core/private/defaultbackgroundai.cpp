//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

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
