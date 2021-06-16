//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef GAMERESULT_H
#define GAMERESULT_H

/**
 * @brief The GameResult struct This is simple structure with game statistic.
 */
struct GameResult
{
    /**
     * @brief points This is count of the receved point in game.
     */
    int points = 0;

    /**
     * @brief distance this is the distance traveled for the level.
     */
    int distance = 0;
};

#endif // GAMERESULT_H
