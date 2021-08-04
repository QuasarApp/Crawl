//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef ABSLEVELWORLD_H
#define ABSLEVELWORLD_H

#include "Crawl/iworld.h"

namespace AbstractLvl {

class AbsLvlWorld : public CRAWL::IWorld {

    // IWorld interface
public:

    AbsLvlWorld();


    CRAWL::PlayableObject *initPlayer() const override;
    CRAWL::WorldRule *initWorldRules() override;
    QString initHdrBackGround() const override;
    QString description() const override;
    QString imagePreview() const override;
    QString name() const override;
    int costToUnlock() const override;
    CRAWL::IControl *initUserInterface() const override;
    void initPlayerControl(CRAWL::IControl *control) override;

};

}

#endif // ABSLEVELWORLD_H
