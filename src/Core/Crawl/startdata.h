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
class IItem;
class PlayableObject;

/**
 * @brief The StartData class This class contains arguments for starting new game session.
 */
class CRAWL_EXPORT StartData
{
public:

    StartData(const User * player, IItem *snake);

    /**
     * @brief player This method return pointer to user that will be control player snake.
     * @return pointer to user that will be control player snake.
     * @see StartData::setPlayer
     */
    const User *player() const;

    /**
     * @brief setPlayer This method sets
     * @param newPlayer This is new object of the user.
     * @see StartData::player
     */
    void setPlayer(const User *newPlayer);

    /**
     * @brief snake This method return pointer to snake object that selected player.
     * @return pointer to snake object that selected player.
     */
    IItem *snake() const;

    /**
     * @brief setSnake This method sets new pointer of the selected snake.
     * @param newSnake This is pointer of the selected items.
     */
    void setSnake(IItem *newSnake);

private:
    const User *_player = nullptr;
    IItem *_snake = nullptr;
};

}

#endif // STARTDATA_H
