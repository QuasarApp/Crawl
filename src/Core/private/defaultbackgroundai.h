//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef DEFAULTBACKGROUNDAI_H
#define DEFAULTBACKGROUNDAI_H

#include "SnakeProject/defaultcontrol.h"
#include <SnakeProject/iai.h>

class QTimer;

class DefaultBackgroundAI: public DefaultControl, public IAI {
    Q_OBJECT
public:
    DefaultBackgroundAI();
    ~DefaultBackgroundAI();

    // IAI interface
public:
    void startAI() override;
    void stopAI() override;

private slots:
    void handleTimerTriger();

private:
    QTimer *_timer = nullptr;
};

#endif // DEFAULTBACKGROUNDAI_H
