//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef STARTDATA_H
#define STARTDATA_H

namespace CRAWL {

class User;
class PlayableObject;

/**
 * @brief The StartData class This class contains arguments for starting new game session.
 */
class StartData
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

private:
    User *_player = nullptr;
    int _snakeType;
};

}

#endif // STARTDATA_H
