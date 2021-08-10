//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef IPREVIEWSCANEWORLD_H
#define IPREVIEWSCANEWORLD_H

#include "iworld.h"

namespace CRAWL {

/**
 * @brief The IPreviewScaneWorld class is interface of the all preview scanes models.
 */
class CRAWL_EXPORT IPreviewScaneWorld: public IWorld
{
public:
    IPreviewScaneWorld();

    // IItem interface
public:
    QString itemTextId() const override final;
    QString itemName() const override final;
    QString description() const override final;
    QString image() const override final;
    int cost() const override final;
    int requiredTier() const override final;

    bool start(const StartData &config) override;
    bool stop() override;

signals:
    void sigPrepareIsFinished(const StartData& config);

private:
    StartData _configuration;
};

}
#endif // IPREVIEWSCANEWORLD_H
