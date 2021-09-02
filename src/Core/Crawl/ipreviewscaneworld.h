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

class AvailableSnakesModel;
class InventoryModel;

/**
 * @brief The IPreviewScaneWorld class is interface of the all preview scanes models.
 */
class CRAWL_EXPORT IPreviewScaneWorld: public IWorld
{
    Q_OBJECT

    /**
     * availableSnakesModel This property contais pointer to the model of the available snakes in view.
     * @see IPreviewScaneWorld::availableSnakesModelChanged
     * @see IPreviewScaneWorld::getAvailableSnakesModel
     * @see IPreviewScaneWorld::setAvailableSnakesModel
    */
    Q_PROPERTY(QObject * availableSnakesModel READ getAvailableSnakesModel NOTIFY availableSnakesModelChanged)

    /**
     * availableItemsModel This property contais pointer to the model of the available items in view.
     * @see IPreviewScaneWorld::getAvailableItemsModel
     * @see IPreviewScaneWorld::availableItemsModelChanged
    */
    Q_PROPERTY(QObject * availableItemsModel READ getAvailableItemsModel NOTIFY availableItemsModelChanged)

public:
    /**
     * @brief IPreviewScaneWorld This is main constructo of the preview world model.
     * @param mainWorld This pointer to the main world. This is needed for correctly working initPalayer methods. The implementation of the some methods should be identy with the main world.
     */
    IPreviewScaneWorld();

    // IItem interface
public:
    QString itemTextId() const override final;
    QString itemName() const override final;
    QString description() const override final;
    QString image() const override final;
    int cost() const override final;
    int requiredTier() const override final;
    void initControl(IControl *control) override;
    IControl* initUserInterface() const override;
    bool start(const StartData &config) override;

    bool stop() override;

    /**
     * @brief getAvailableSnakesModel This method return current model of the available snakes view.
     * @return current model of the available snakes view.
     * @see IPreviewScaneWorld::availableSnakesModelChanged
     * @see IPreviewScaneWorld::setAvailableSnakesModel
     * @see IPreviewScaneWorld::availableSnakesModel
     */
    QObject *getAvailableSnakesModel() const;

    /**
     * @brief getAvailableItemsModel This method return current model of the items view.
     * @return current model of the items view.
     * @see IPreviewScaneWorld::availableItemsModelChanged
     * @see IPreviewScaneWorld::availableItemsModel
     */
    QObject *getAvailableItemsModel() const;

signals:
    /**
     * @brief sigPrepareIsFinished This signal emited when user finished prepare to game.
     * @param config This is data for start.
     */
    void sigPrepareIsFinished(const StartData& config);

    /**
     * @brief availableSnakesModelChanged This signale emited when the availableSnakes model changed.
     * @see IPreviewScaneWorld::setAvailableSnakesModel
     * @see IPreviewScaneWorld::getAvailableSnakesModel
     * @see IPreviewScaneWorld::availableSnakesModel
     */
    void availableSnakesModelChanged();

    /**
     * @brief availableItemsModelChanged This signal emited when items view model changed.
     * @see IPreviewScaneWorld::getAvailableItemsModel
     * @see IPreviewScaneWorld::availableItemsModel
     */
    void availableItemsModelChanged();

protected:
    /**
     * @brief setAvailableSnakesModel This method sets new model for snakes view.
     * @param newAvailableSnakesModel This is new model of snakes view.
     * @see IPreviewScaneWorld::availableSnakesModelChanged
     * @see IPreviewScaneWorld::getAvailableSnakesModel
     * @see IPreviewScaneWorld::availableSnakesModel
     */
    void setAvailableSnakesModel(AvailableSnakesModel *newAvailableSnakesModel);


private slots:

    void handleRotation(double x, double y);
    void handleStart();
    void handleSelect(int item, bool isSelected);

private:
    QHash<int, IItem *> _availableSnakes;
    AvailableSnakesModel *_availableSnakesModel = nullptr;
    const User* _user = nullptr;
    InventoryModel *_availableItemsModel = nullptr;
};

}
#endif // IPREVIEWSCANEWORLD_H
