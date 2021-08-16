//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef ABSNEST_H
#define ABSNEST_H
#include <Crawl/ipreviewscaneworld.h>


namespace AbstractLvl {

/**
 * @brief The AbsNest class Abstrcat nest level
 */
class AbsNest: public CRAWL::IPreviewScaneWorld
{
public:
    AbsNest(IWorld *mainWorld);

    // IWorld interface
public:
    CRAWL::WorldRule *initWorldRules() override;
    QString initHdrBackGround() const override;

};

}
#endif // ABSNEST_H
