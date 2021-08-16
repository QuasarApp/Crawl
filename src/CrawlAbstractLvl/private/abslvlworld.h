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

    CRAWL::PlayableObject *initPlayer(int type) const override;
    CRAWL::WorldRule *initWorldRules() override;
    QString initHdrBackGround() const override;
    QString description() const override;
    QString image() const override;
    QString itemName() const override;
    int cost() const override;
    CRAWL::IControl *initUserInterface() const override;
    void initControl(CRAWL::IControl *control) override;
    QString itemTextId() const override;
    int requiredTier() const override;

};

}

#endif // ABSLEVELWORLD_H
