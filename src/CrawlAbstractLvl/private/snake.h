//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef SNAKE_H
#define SNAKE_H

#include "Crawl/iplayer.h"

class Snake : public IPlayer {

    Q_OBJECT

public:
    Snake();
    void setControl(const IControl *control) override;

    // IWorldItem interface
protected:
    void onIntersects(const IWorldItem *item) override;

protected:
    void onTap() override;

};

#endif // SNAKE_H
