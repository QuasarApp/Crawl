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
    Q_OBJECT
public:
    /**
     * @brief IPreviewScaneWorld This is main constructo of the preview world model.
     * @param mainWorld This pointer to the main world. This is needed for correctly working initPalayer methods. The implementation of the some methods should be identy with the main world.
     */
    IPreviewScaneWorld(const IWorld* mainWorld);

    // IItem interface
public:
    QString itemTextId() const override final;
    QString itemName() const override final;
    QString description() const override final;
    QString image() const override final;
    int cost() const override final;
    int requiredTier() const override final;
    PlayableObject *initPlayer(int objectType) const override final;
    void initControl(IControl *control) override;
    IControl* initUserInterface() const override;
    bool start(const StartData &config) override;
    bool stop() override;

    const StartData &configuration() const;

signals:
    /**
     * @brief sigPrepareIsFinished This signal emited when user finished prepare to game.
     * @param config This is data for start.
     */
    void sigPrepareIsFinished(const StartData& config);

private slots:

    void handleRotation(double x, double y);
    void handleStart();
    void handleSelect(int item, bool isSelected);

private:
    StartData _configuration;
    const IWorld* _mainWorld;


};

}
#endif // IPREVIEWSCANEWORLD_H
