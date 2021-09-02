//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef GAMESESSION_H
#define GAMESESSION_H

namespace CRAWL {

/**
 * @brief The GameSession class contains all temp information that changed during game session.
 */
class GameSession
{
public:
    GameSession();

    /**
     * @brief xp This is game session experience of the current user.
     * @return current value of the experiance
     */
    int xp() const;

    /**
     * @brief setXp This method sets new vaue of the xperiance
     * @param newXp This is new value of the experiance durring game session.
     */
    void setXp(int newXp);

    /**
     * @brief money This method return received during game session money
     * @return received during game session money
     */
    int money() const;

    /**
     * @brief setMoney This method sets new value of money
     * @param newMoney This is new value of money
     */
    void setMoney(int newMoney);

private:
    int _xp = 0;
    int _money = 0;

};
}
#endif // GAMESESSION_H
