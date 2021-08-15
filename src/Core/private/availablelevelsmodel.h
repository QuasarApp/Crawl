//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef AVAILABLELEVELSMODEL_H
#define AVAILABLELEVELSMODEL_H

#include "baseuserlistmodel.h"

namespace CRAWL {

class User;
class IItem;

/**
 * @brief The AvailableLevelsModel class is model of the available levels qml view.
 * This model just show available levels of the current user.
 * @see the SelectLevelView.qml module.
 */
class AvailableLevelsModel: public BaseUserListModel
{
    Q_OBJECT
    /**
     * @brief  currentLevel This property contains id of the loaded level.
     * @see AvailableLevelsModel::getCurrentLevel
     * @see AvailableLevelsModel::setCurrentLevel
     * @see AvailableLevelsModel::currentLevelChanged
    */
    Q_PROPERTY(int currentLevel READ getCurrentLevel WRITE setCurrentLevel NOTIFY currentLevelChanged)

public:
    AvailableLevelsModel();

    /**
     * @brief getCurrentLevel This method return value of the curernt level property
     * @return value of the curernt level property
     * @see AvailableLevelsModel::currentLevel
     * @see AvailableLevelsModel::setCurrentLevel
     * @see AvailableLevelsModel::currentLevelChanged
     */
    int getCurrentLevel() const;

    /**
     * @brief setCurrentLevel This method sets new current level.
     * @param newCurrentLevel This is new value of the current level.
     * @see AvailableLevelsModel::getCurrentLevel
     * @see AvailableLevelsModel::currentLevel
     * @see AvailableLevelsModel::currentLevelChanged
     */
    void setCurrentLevel(int newCurrentLevel);

    /**
     * @brief select This method select new level of user.
     * @param levelId This is id of the selected level.
     */
    Q_INVOKABLE void select(int levelId);


signals:
    /**
     * @brief currentLevelChanged This signal emited when the currentLevel propertye is changed.
     * @see AvailableLevelsModel::getCurrentLevel
     * @see AvailableLevelsModel::setCurrentLevel
     * @see AvailableLevelsModel::currentLevel
     */
    void currentLevelChanged();

    /**
     * @brief sigUserSelectLevel This signal emited when user select new level.
     * @param level This is level id that user selected.
     */
    void sigUserSelectLevel(int level);

private:
    int currentLevel = -1;

};

}
#endif // AVAILABLELEVELSMODEL_H
