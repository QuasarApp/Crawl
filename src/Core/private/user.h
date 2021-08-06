//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include <QSet>

#ifndef USER_H
#define USER_H

namespace CRAWL {

/**
 * @brief The User class This is internal class for collection all user data and user state.
 */
class User
{
public:
    User();

private:
    int _moneu = 0;
    int _lvl = 0;
    QSet<int> _unlockedItems;

};
}

#endif // USER_H
