//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef WORLD_H
#define WORLD_H

#include "Crawl/iworld.h"

class World : public IWorld {

    // IWorld interface
public:

    World();

    WorldRule *initWorldRules() override;
    QString initHdrBackGround() const override;
    QString description() const override;
    QString imagePreview() const override;
    QString name() const override;
    int costToUnlock() const override;
    IControl *initUserInterface() const override;
    void initPlayerControl(IControl *control) override;
    IPlayer *initPlayer() const override;
    IAI *initBackGroundAI() const override;

private slots:
    void handleXViewChanged(double dx);
    void handleYViewChanged(double dy);

};

#endif // WORLD_H
