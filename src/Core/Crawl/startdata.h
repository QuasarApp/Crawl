//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include <QList>
#include <QSet>
#include "global.h"

#ifndef STARTDATA_H
#define STARTDATA_H

namespace CRAWL {

class User;
class PlayableObject;

/**
 * @brief The StartData class This class contains arguments for starting new game session.
 */
class CRAWL_EXPORT StartData
{
public:
    StartData();

    StartData(User * player, int snake);

    /**
     * @brief player This method return pointer to user that will be control player snake.
     * @return pointer to user that will be control player snake.
     * @see StartData::setPlayer
     */
    User *player() const;

    /**
     * @brief setPlayer This method sets
     * @param newPlayer This is new object of the user.
     * @see StartData::player
     */
    void setPlayer(User *newPlayer);

    /**
     * @brief snakeType This method return select for game snake object type.
     * @return select for game snake object.
     * @see StartData::setSnakeType
     */
    int snakeType() const;

    /**
     * @brief setSnakeType This method sets new selected for game object type,
     * @param newSnake This is  new selected for game object
     * @see StartData::snakeType
     */
    void setSnakeType(int newSnake);

    /**
     * @brief snakePerks This method return the list of the used snake upgrades.
     * @return list of the used upgrades of the snake.
     * @see StartData::setSnakePerks
     */
    const QSet<int> &snakePerks() const;

    /**
     * @brief setSnakePerks This method sets new list of the used upgrades.
     * @param newSnakePerks This is list of the used upgrades.
     * @see StartData::snakePerks
     */
    void setSnakePerks(const QSet<int> &newSnakePerks);

private:
    User *_player = nullptr;
    int _snakeType;
    QSet<int> _snakePerks;
};

}

#endif // STARTDATA_H
