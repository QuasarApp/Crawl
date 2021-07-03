//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef TESTSNAKE_H
#define TESTSNAKE_H

#include "Crawl/snake.h"

class TestSnake : public Snake {

    Q_OBJECT

public:
    TestSnake();

    // IWorldItem interface
protected:
    void onIntersects(const IWorldItem *item) override;

};

#endif // TESTSNAKE_H