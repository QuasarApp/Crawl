//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef AVAILABLESNAKESVIEW_H
#define AVAILABLESNAKESVIEW_H

#include "baseuserlistmodel.h"

namespace CRAWL {

/**
 * @brief The AvailableSnakesModel class This is list model for view available snakes in the level.
 */
class AvailableSnakesModel: public BaseUserListModel
{
    Q_OBJECT

    /**
     * @brief  currentSnake This property contains id of the showed snake.
     * @see AvailableLevelsModel::getCurrentSnake
     * @see AvailableLevelsModel::setCurrentSnake
     * @see AvailableLevelsModel::currentSnakeChanged
    */
    Q_PROPERTY(int currentSnake READ getCurrentSnake WRITE setCurrentSnake NOTIFY currentSnakeChanged)


public:
    AvailableSnakesModel();

    /**
     * @brief getCurrentSnake This method return current value of the currentSnake property
     * @return current value of the currentSnake property
     * @see AvailableLevelsModel::currentSnake
     * @see AvailableLevelsModel::setCurrentSnake
     * @see AvailableLevelsModel::currentSnakeChanged
     */
    int getCurrentSnake() const;

    /**
     * @brief setCurrentSnake This method change current value of the currentSnake property
     * @param newCurrentSnake This is new value of the currentSnake property
     * @see AvailableLevelsModel::getCurrentSnake
     * @see AvailableLevelsModel::currentSnake
     * @see AvailableLevelsModel::currentSnakeChanged
     */
    void setCurrentSnake(int newCurrentSnake);
signals:

    /**
     * @brief currentSnakeChanged This signale emited when the currentSnake property changed.
     * @see AvailableLevelsModel::getCurrentSnake
     * @see AvailableLevelsModel::setCurrentSnake
     * @see AvailableLevelsModel::currentSnake
    */
    void currentSnakeChanged();

private:
    int _currentSnake;

};
}
#endif // AVAILABLESNAKESVIEW_H
