//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef PLAYER_H
#define PLAYER_H

#include "icontrol.h"


namespace CRAWL {

class User;

/**
 * @brief The Player class is main class of users.
 */
class CRAWL_EXPORT Player: public IControl
{
    Q_OBJECT
public:
    Player();

    /**
     * @brief addXp This method add new xp to palyer.
     * @param newXp this is value of experience
     */
    void addXp(int newXp);

    /**
     * @brief addMoney This method add money to user.
     * @param money added amount of money
     */
    void addMoney(int money);

    /**
     * @brief userData This method sets user that control this object.
     * @return current control user.
     */
    User *userData() const;

    /**
     * @brief setUserData This method sets user that control this object.
     * @param newUserData This is new pointer of the new user.
     */
    void setUserData(User *newUserData);

private:

    User *_userData = nullptr;
};
}
#endif // PLAYER_H
